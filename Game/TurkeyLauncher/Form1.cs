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
        static bool debug = true;
        static string enginePath = debug ? "" : "engine/";
        static string configPath = debug ? "" : "config/";
        static string assetPath = enginePath + "mge/";
        static string texturePath = assetPath + "textures/";
        static string userListPath = assetPath + "customMapLists/";

        public frmLauncher()
        {
            InitializeComponent();



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
            InitializeADL();

            InvalidateResolutions();

            //AddPlaylist();

            if (System.IO.File.Exists(texturePath + "banner.png"))
            {
                pbBanner.Image = System.Drawing.Bitmap.FromFile(texturePath + "banner.png");
            }

            if (!System.IO.File.Exists(enginePath + "mge.exe"))
            {
                Debug.LogGen(LoggingChannel.ERROR, "Engine could not be found. Please reinstall.");
                //Application.Exit();

                InvalidateUserMapLists();
                btnPlaygroundMode.Enabled = false;
                btnStoryMode.Enabled = false;
            }

            InvalidateUserMapLists();

            Control.CheckForIllegalCrossThreadCalls = false;
            this.BringToFront();
            this.MouseEnter += FrmLauncher_Enter;
            this.FormClosing += FrmLauncher_FormClosing;
            adlConsole.Hide(); //Make sure its not crashing through crossthreadcalls
            adlConsole.FormClosing += AdlConsole_FormClosing;
            Control.CheckForIllegalCrossThreadCalls = true;
        }

        private void FrmLauncher_Enter(object sender, EventArgs e)
        {
            if (windowClosed) cbShowConsole.Checked = false;
            windowClosed = false;
        }



        private void FrmLauncher_FormClosing(object sender, FormClosingEventArgs e)
        {
            overrideConsoleClose = true;
        }

        bool windowClosed = false;


        bool overrideConsoleClose = false;

        private void AdlConsole_FormClosing(object sender, FormClosingEventArgs e)
        {

            if (overrideConsoleClose) return;
            e.Cancel = true;
            adlConsole.Hide();

            Control.CheckForIllegalCrossThreadCalls = false;
            windowClosed = true;
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

                GameConsoleRedirector gcr = GameConsoleRedirector.CreateRedirector(_engine.StandardOutput, _engine.StandardError, _engine);
                gcr.StartThreads();

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


            if (System.IO.File.Exists(assetPath + "enginesettings.lua"))
                System.IO.File.Delete(assetPath + "enginesettings.lua");

            System.IO.TextWriter tw = new System.IO.StreamWriter(assetPath + "enginesettings.lua");
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

            if (System.IO.Directory.Exists(userListPath))
            {
                foreach (string s in System.IO.Directory.GetFiles(userListPath, "*.lua"))
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
            if (cobMaplist.SelectedIndex < 1)
            {
                AddPlaylist();
            }
            CompileLuaEngineSettings(resolutions[cobResolutions.SelectedIndex].X, resolutions[cobResolutions.SelectedIndex].Y,
                    msaaSamples, cbVSync.Checked, cbWindowed.Checked);
            StartEngine(CreateLaunchArgs(false));
        }

        private void cobMSAASamples_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (cobMSAASamples.SelectedIndex < 1) msaaSamples = 0;
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

        void AddPlaylist()
        {
            if (ofdLoadMaplist.ShowDialog() == DialogResult.OK)
            {
                string source = System.IO.Path.GetFullPath(ofdLoadMaplist.FileName);
                int lastInd = source.LastIndexOf("\\") + 1;
                string name = source.Substring(lastInd, source.Length - lastInd);
                cobMaplist.Items.Add(name);
                string path = "./" + userListPath + name;
                Debug.LogGen(LoggingChannel.LOG, source);
                Debug.LogGen(LoggingChannel.LOG, path);
                System.IO.File.Copy(source, path);
                userMaplist.Add(path);
                cobMaplist.SelectedIndex = cobMaplist.Items.Count - 1;
            }
        }

        private void cobMaplist_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (cobMaplist.SelectedIndex == 0)
            {
                AddPlaylist();
            }
        }
    }
}
