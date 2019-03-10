using System.IO;
using System.Threading;
using System.Diagnostics;
using ADL;
namespace TurkeyLauncher
{
    public class GameConsoleRedirector
    {
        Thread thread = null;
        Thread errThread = null;
        TextReader cOut;
        TextReader cEOut;
        Process _engineProc;

        public GameConsoleRedirector()
        {
            //SHIT
        }

        public static GameConsoleRedirector CreateRedirector(StreamReader consoleOut, StreamReader errorConsoleOut, Process engine)
        {
            GameConsoleRedirector gcr = new GameConsoleRedirector();
            gcr._engineProc = engine;
            gcr.cEOut = errorConsoleOut;
            gcr.cOut = consoleOut;
            return gcr;
        }

        public void StartThreads()
        {
            if (thread == null)
            {
                thread = new Thread(() => Start(cOut, (int)LoggingChannel.MGE_ENGINE_CONSOLE_OUT));

            }
            else
            {
                thread.Abort();
            }

            if (errThread == null)
            {
                errThread = new Thread(() => Start(cEOut, (int)LoggingChannel.MGE_ENGINE_CONSOLE_ERR_OUT));
            }
            else
            {
                errThread.Abort();
            }
            errThread.Start();
            thread.Start();
        }

        public void StopThreads()
        {
            if (thread == null && errThread == null) return;
            if (thread != null) thread.Abort();
            if (errThread != null) errThread.Abort();
        }

        public void Start(TextReader cout, int channelID)
        {
            string txt = "";
            while (!_engineProc.HasExited)
            {
                txt = cout.ReadLine();
                if (txt != "") ADL.Debug.Log(channelID, txt);
            }
        }

    }
}
