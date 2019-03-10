using System;
using System.Runtime.InteropServices;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Collections.Generic;
using ADL;
using ADL.CustomCMD;

namespace TurkeyLauncher
{


    public enum LoggingChannel
    {
        GENERAL = 1,
        LOG = 2,
        WARNING = 4,
        ERROR = 8,
        ADL = 16,
        MGE_ENGINE_CONSOLE_OUT = 32,
        MGE_ENGINE_CONSOLE_ERR_OUT = 64
    }

    public partial class frmLauncher : Form
    {

        #region MagicLines
        [DllImport("user32.dll")]
        public static extern bool EnumDisplaySettings(
          string deviceName, int modeNum, ref DEVMODE devMode);
        const int ENUM_CURRENT_SETTINGS = -1;

        const int ENUM_REGISTRY_SETTINGS = -2;

        [StructLayout(LayoutKind.Sequential)]
        public struct DEVMODE
        {

            private const int CCHDEVICENAME = 0x20;
            private const int CCHFORMNAME = 0x20;
            [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 0x20)]
            public string dmDeviceName;
            public short dmSpecVersion;
            public short dmDriverVersion;
            public short dmSize;
            public short dmDriverExtra;
            public int dmFields;
            public int dmPositionX;
            public int dmPositionY;
            public ScreenOrientation dmDisplayOrientation;
            public int dmDisplayFixedOutput;
            public short dmColor;
            public short dmDuplex;
            public short dmYResolution;
            public short dmTTOption;
            public short dmCollate;
            [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 0x20)]
            public string dmFormName;
            public short dmLogPixels;
            public int dmBitsPerPel;
            public int dmPelsWidth;
            public int dmPelsHeight;
            public int dmDisplayFlags;
            public int dmDisplayFrequency;
            public int dmICMMethod;
            public int dmICMIntent;
            public int dmMediaType;
            public int dmDitherType;
            public int dmReserved1;
            public int dmReserved2;
            public int dmPanningWidth;
            public int dmPanningHeight;

        }
        #endregion

        CustomCMDForm adlConsole;

        System.Diagnostics.Process _engine = null;

        List<System.Drawing.Point> resolutions;
        List<string> userMaplist = new List<string>();
        int msaaSamples = 0;

        string enginePath = "";
        string configPath = "";

        public frmLauncher()
        {
            InitializeComponent();

            InitializeADL();

            InvalidateResolutions();

            if(System.IO.File.Exists(enginePath + "mge/textures/banner.png"))
            {
                pbBanner.Image = System.Drawing.Bitmap.FromFile(enginePath + "mge/textures/banner.png");
            }

            if (!System.IO.File.Exists(enginePath + "mge.exe"))
            {
                Debug.LogGen(LoggingChannel.ERROR, "Engine could not be found. Please reinstall.");
                //Application.Exit();
                btnPlaygroundMode.Enabled = false;
                btnStoryMode.Enabled = false;
            }


        }



        void InitializeADL()
        {
            Debug.LoadConfig(configPath + "adl_config.xml");
            Debug.SendWarnings = true;
            Debug.SendUpdateMessageOnFirstLog = true;

            Debug.PrefixLookupMode = ADL.Configs.PrefixLookupSettings.ADDPREFIXIFAVAILABLE |
                                    ADL.Configs.PrefixLookupSettings.DECONSTRUCTMASKTOFIND; //If you have int.minvalue to int.maxvalue channels this is not really advisable. (Config files can be bloated by baked prefixes thus getting a huge size.)

            ADL.Streams.PipeStream ps = new ADL.Streams.PipeStream();

            ADL.Streams.LogStream ls = new ADL.Streams.LogStream(
                ps,
                new BitMask<LoggingChannel>(true),
                MatchType.MATCH_ONE,
                true);

            Debug.AddOutputStream(ls);
            Debug.ADLEnabled = true;

            adlConsole = (CustomCMDForm)CMDUtils.CreateCustomConsole(ps, configPath + "adl_customcmd_config.xml");
            adlConsole.MaxConsoleLogCount = 5000;
            adlConsole.MaxLogCountPerFrame = 500;
            adlConsole.MaxLogCountPerBlock = 2500;

        }

        private void checkBox1_CheckedChanged(object sender, EventArgs e)
        {
            Control.CheckForIllegalCrossThreadCalls = false;
            if (!cbShowConsole.Checked) adlConsole.Hide();
            else adlConsole.Show();
            this.BringToFront();
            Control.CheckForIllegalCrossThreadCalls = true;
        }

        private void frmLauncher_Load(object sender, EventArgs e)
        {
            InvalidateUserMapLists();
            Control.CheckForIllegalCrossThreadCalls = false;
            this.BringToFront();
            adlConsole.Hide(); //Make sure its not crashing through crossthreadcalls
            Control.CheckForIllegalCrossThreadCalls = true;
        }

        private void frmLauncher_Close(object sender, EventArgs e)
        {
            Application.Exit();
        }

        void InvalidateResolutions()
        {
            Debug.LogGen(LoggingChannel.LOG, "Loading Resolutions...");
            resolutions = new List<System.Drawing.Point>();
            cobResolutions.Items.Clear();

            DEVMODE dmode = new DEVMODE();
            int i = 0;

            while (EnumDisplaySettings(null, i, ref dmode))
            {
                System.Drawing.Point p = new System.Drawing.Point(dmode.dmPelsWidth, dmode.dmPelsHeight);
                if (i == 0 || (p.X != resolutions[resolutions.Count - 1].X && p.Y != resolutions[resolutions.Count - 1].Y))
                {
                    resolutions.Add(p);
                    cobResolutions.Items.Add(p.X + " x " + p.Y);
                    Debug.LogGen(LoggingChannel.LOG, "Adding Resolution: " + resolutions[resolutions.Count - 1]);
                }

                i++;
            }

            cobResolutions.SelectedIndex = cobResolutions.Items.Count - 1;
        }

        void StartEngine(string args)
        {
            if (_engine != null && !_engine.HasExited)
                _engine.Kill();

            System.Diagnostics.ProcessStartInfo psi = new System.Diagnostics.ProcessStartInfo(enginePath + "mge.exe", args);

            psi.CreateNoWindow = true;
            psi.RedirectStandardError = true;
            psi.RedirectStandardOutput = true;
            psi.UseShellExecute = false;

            _engine = new System.Diagnostics.Process();
            _engine.StartInfo = psi;

            try
            {
                _engine.Start();
                if(cbShowConsole.Checked)
                {
                    GameConsoleRedirector gcr = GameConsoleRedirector.CreateRedirector(_engine.StandardOutput, _engine.StandardError, _engine);
                    gcr.StartThreads();
                }
            }
            catch (Exception)
            {

                MessageBox.Show("Error, could not run mge.exe");
                Debug.LogGen(LoggingChannel.ERROR | LoggingChannel.GENERAL, "Error, could not run mge.exe");
            }

        }

        void CompileLuaEngineSettings(int width, int height, int msaaSamples, bool vSync, bool windowMode)
        {
            List<string> settings = new List<string>();
            settings.Add("FPSTarget = 120");
            settings.Add("WindowName = \"Turkey Game\"");
            settings.Add("width = " + width);
            settings.Add("height = " + height);
            settings.Add("vSync = " + (vSync ? 1 : 0));
            settings.Add("windowMode = " + (windowMode ? 1 : 0));
            settings.Add("msaaSamples = " + msaaSamples);
            

            if (System.IO.File.Exists(enginePath + "mge/enginesettings.lua"))
                System.IO.File.Delete(enginePath + "mge/enginesettings.lua");

            System.IO.TextWriter tw = new System.IO.StreamWriter(enginePath + "mge/enginesettings.lua");
            try
            {
                for (int i = 0; i < settings.Count; i++)
                {
                    tw.WriteLine(settings[i]);
                }
                tw.Close();
            }
            catch (Exception)
            {
                Debug.LogGen(LoggingChannel.ERROR, "Could not create engine setings.");
            }
        }

        string CreateLaunchArgs(bool storyMode)
        {
            string ret = "";
            if (!storyMode) ret += " -p " + userMaplist[cobMaplist.SelectedIndex - 1];
            return ret;
        }

        void InvalidateUserMapLists()
        {
            cobMaplist.Items.Clear();
            cobMaplist.Items.Add("Add to List");
            userMaplist.Clear();

            if (System.IO.Directory.Exists(enginePath + "mge/customMapLists/"))
            {
                foreach (string s in System.IO.Directory.GetFiles(enginePath + "mge/customMapLists/", "*.lua"))
                {
                    userMaplist.Add(System.IO.Path.GetFullPath(s));
                    int lastInd = s.LastIndexOf("/") + 1;
                    cobMaplist.Items.Add(s.Substring(lastInd, s.Length - lastInd));
                }
                if (cobMaplist.Items.Count > 1) cobMaplist.SelectedIndex = 1;
            }
        }

        private void btnPlaygroundMode_Click(object sender, EventArgs e)
        {
            if(cobMaplist.SelectedIndex < 1)
            {
                if(ofdLoadMaplist.ShowDialog() == DialogResult.OK)
                {
                    string s = System.IO.Path.GetFullPath(ofdLoadMaplist.FileName);
                    int lastInd = s.LastIndexOf("/") + 1;
                    string st = s.Substring(lastInd, s.Length - lastInd);
                    cobMaplist.Items.Add(st);
                    userMaplist.Add(s);
                    cobMaplist.SelectedIndex = cobMaplist.Items.Count - 1;
                }
            }
            CompileLuaEngineSettings(resolutions[cobResolutions.SelectedIndex].X, resolutions[cobResolutions.SelectedIndex].Y,
                    msaaSamples, cbVSync.Checked, cbWindowed.Checked);
            StartEngine(CreateLaunchArgs(false));
        }

        private void cobMSAASamples_SelectedIndexChanged(object sender, EventArgs e)
        {
            if(cobMSAASamples.SelectedIndex < 1)msaaSamples = 0;
            msaaSamples = (int)Math.Pow(2, cobMSAASamples.SelectedIndex);
        }

        private void cobResolutions_SelectedIndexChanged(object sender, EventArgs e)
        {

        }

        private void btnStoryMode_Click(object sender, EventArgs e)
        {
            CompileLuaEngineSettings(resolutions[cobResolutions.SelectedIndex].X, resolutions[cobResolutions.SelectedIndex].Y,
                    msaaSamples, cbVSync.Checked, cbWindowed.Checked);
            StartEngine(CreateLaunchArgs(true));
        }
    }
}
