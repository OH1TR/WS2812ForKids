using System;
using System.Collections.Generic;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LedController
{
    class Program
    {
        static SerialPort port;

        static void Main(string[] args)
        {
            OpenSerial();

            int i, a;

            while (true)
            {
                /*
                for (i = 0; i < 30; i++)
                {
                    SetLed(i, i * 5, 150 - i * 5, 100);
                }
                Show();
                */
                
                for (a = 0; a < 30; a++)
                {
                    for (i = 0; i < 30; i++)
                    {
                        SetLed(i, 0, 0, 0);
                    }
                    SetLed(a, 255, 0, 0);
                    Show();
                }

                for (a = 30; a >= 0; a--)
                {
                    for (i = 0; i < 30; i++)
                    {
                        SetLed(i, 0, 0, 0);
                    }
                    SetLed(a, 0, 255, 0);
                    Show();
                }
            }
        }

        static void OpenSerial()
        {
            port = new SerialPort("COM3");
            port.BaudRate = 115200;
            port.DataBits = 8;
            port.Parity = Parity.None;
            port.StopBits = StopBits.One;
            port.Handshake = Handshake.None;
            port.Open();
        }

        static void SetLed(int led, int r, int g, int b)
        {
            string cmd = "S" + led.ToString("X2") + r.ToString("X2") + g.ToString("X2") + b.ToString("X2") + Environment.NewLine;
            byte[] cmdBuf = ASCIIEncoding.ASCII.GetBytes(cmd);
            port.Write(cmdBuf, 0, cmdBuf.Length);
        }

        static void Show()
        {
            string cmd = "D" + Environment.NewLine;
            byte[] cmdBuf = ASCIIEncoding.ASCII.GetBytes(cmd);
            port.Write(cmdBuf, 0, cmdBuf.Length);
            System.Threading.Thread.Sleep(5);
        }
    }
}
