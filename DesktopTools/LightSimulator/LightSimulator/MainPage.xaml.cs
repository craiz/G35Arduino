using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Primitives;
using Windows.UI.Xaml.Data;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Navigation;


// The Blank Page item template is documented at http://go.microsoft.com/fwlink/?LinkId=234238

namespace LightSimulator
{
    /// <summary>
    /// An empty page that can be used on its own or navigated to within a Frame.
    /// </summary>
    public sealed partial class MainPage : Page
    {
        private List<LightBulb> bulbs = null;
        private UInt16 bulb_count = 36;
        private ColorNodeSimulator.Class1 simulator = null;
        private Object lockObject = new Object();
        DispatcherTimer timer = new DispatcherTimer();

        // Window Small Layout
        private List<LightBulb> bulbs_left = null;
        private List<LightBulb> bulbs_right = null;
        private List<LightBulb> bulbs_top = null;
        private List<LightBulb> bulbs_bottom = null;

        public MainPage()
        {
            this.InitializeComponent();

            simulator = new ColorNodeSimulator.Class1();
            simulator.Configure(bulb_count);

            bulbs = new LightString(bulb_count);
            LightBulbs.ItemsSource = bulbs;

            // Window Small Layout
            bulbs_left = new LightString(10);
            bulbs_top = new LightString(8);
            bulbs_right = new LightString(10);
            bulbs_bottom = new LightString(8);
            LightsLeft.ItemsSource = bulbs_left;
            LightsTop.ItemsSource = bulbs_top;
            LightsRight.ItemsSource = bulbs_right;
            LightsBottom.ItemsSource = bulbs_bottom;

            timer.Tick += timer_Tick;
        }

        /// <summary>
        /// Invoked when this page is about to be displayed in a Frame.
        /// </summary>
        /// <param name="e">Event data that describes how this page was reached.  The Parameter
        /// property is typically used to configure the page.</param>
        protected override void OnNavigatedTo(NavigationEventArgs e)
        {
        }

        

        private void DissolveButton_Click(object sender, RoutedEventArgs e)
        {
            //byte pattern = (1 << 6) | (4 << 3) | (2);
            //byte pattern = (0 << 6) | (4 << 3) | (2);
            byte pattern = 0;
            byte option = 0x02;
            UInt16 delay = 10;

            SetupLightProgram(ColorNodeSimulator.LightProgramType.Dissolve, pattern, option, delay);
        }

        private void DripFillButton_Click(object sender, RoutedEventArgs e)
        {
            byte pattern = 0;
            byte option = 0;// 0x3E;
            UInt16 delay = 50;

            SetupLightProgram(ColorNodeSimulator.LightProgramType.DripFill, pattern, option, delay);
        }

        private void WaveButton_Click(object sender, RoutedEventArgs e)
        {
            byte pattern = 3;
            byte option = (15 << 4) | 0;
            UInt16 delay = 50;

            SetupLightProgram(ColorNodeSimulator.LightProgramType.Wave, pattern, option, delay);
        }

        private void RandomStrobeButton_Click(object sender, RoutedEventArgs e)
        {
            byte pattern = 10;
            byte option = 0;
            UInt16 delay = 50;

            SetupLightProgram(ColorNodeSimulator.LightProgramType.RandomStrobe, pattern, option, delay);
        }

        private void ShootingStarsButton_Click(object sender, RoutedEventArgs e)
        {
            byte pattern = (4 << 4) | 7; // Color=Cyan, Size=7
            byte option = (1 << 4) | 6; // Speed=1, White Tip, Not Random, No Wait
            UInt16 delay = 50;

            SetupLightProgram(ColorNodeSimulator.LightProgramType.ShootingStar, pattern, option, delay);   
        }

        private void SolidButton_Click(object sender, RoutedEventArgs e)
        {
            byte pattern = 14;
            byte option = 4;
            UInt16 delay = 50;

            SetupLightProgram(ColorNodeSimulator.LightProgramType.Solid, pattern, option, delay);
        }

        private void AlternateDirectionButton_Click(object sender, RoutedEventArgs e)
        {
            byte pattern = 0;
            byte option = 0;
            UInt16 delay = 50;

            SetupLightProgram(ColorNodeSimulator.LightProgramType.AlternateDirection, pattern, option, delay);
        }

        private void FadeSolidButton_Click(object sender, RoutedEventArgs e)
        {
            byte pattern = 14;
            byte option = 4;
            UInt16 delay = 10;

            SetupLightProgram(ColorNodeSimulator.LightProgramType.FadeInFadeOutSolidColors, pattern, option, delay);
        }

        private void ForwardWaveButton_Click(object sender, RoutedEventArgs e)
        {
            byte pattern = 0;
            byte option = 0x0C;
            UInt16 delay = 0;

            SetupLightProgram(ColorNodeSimulator.LightProgramType.ForwardWave, pattern, option, delay);

            update_pattern = 81;
            update_option = 0x04;
            update_delay = delay;
        }

        private byte update_pattern;
        private byte update_option;
        private UInt16 update_delay;

        private void UpdateButton_Click(object sender, RoutedEventArgs e)
        {
            timer.Stop();
            simulator.UpdateLightProgram(update_pattern, update_option, update_delay);
            timer.Interval = new TimeSpan(0);
            timer.Start();
        }

        private void KickButton_Click(object sender, RoutedEventArgs e)
        {
            timer.Stop();
            simulator.KickLightProgram();
            timer.Interval = new TimeSpan(0);
            timer.Start();
        }

        private void SetupLightProgram(ColorNodeSimulator.LightProgramType programType, byte pattern, byte option, UInt16 delay)
        {
            timer.Stop();
            simulator.SetLightProgram(programType, pattern, option, delay);
            timer.Interval = new TimeSpan(0);
            timer.Start();

            update_pattern = pattern;
            update_option = option;
            update_delay = delay;
        }

        void timer_Tick(object sender, object e)
        {
            simulator.DoFrame();
            for (byte i = 0; i < bulb_count; i++)
            {
                ushort color = (ushort)simulator.GetColor(i);
                bulbs[i].BulbColor = color;
                if (i <= 9)
                {
                    // Left
                    // Invert positions
                    /* 9 = 0
                     * 8 = 1
                     * 7 = 2
                     * 6 = 3
                     * 5 = 4
                     * 4 = 5
                     * 3 = 6
                     * 2 = 7
                     * 1 = 8
                     * 0 = 9
                     * */
                    int newI = Math.Abs(i - 9);
                    bulbs_left[newI].BulbColor = color;
                }
                else if (i >= 10 && i <= 17)
                {
                    // Top
                    bulbs_top[i - 10].BulbColor = color;
                }
                else if (i >= 18 && i <= 27)
                {
                    // Right
                    bulbs_right[i - 18].BulbColor = color;
                }
                else
                {
                    // Bottom
                    // Invert positions
                    /* 35 = 0
                     * 34 = 1
                     * 33 = 2
                     * 32 = 3
                     * 31 = 4
                     * 30 = 5
                     * 29 = 6
                     * 28 = 7
                     * */
                    int newI = Math.Abs(i - 35);
                    bulbs_bottom[newI].BulbColor = color;
                }
            }
            
            timer.Stop();
            timer.Interval = new TimeSpan(0, 0, 0, 0, (int)simulator.GetDelay());
            timer.Start();
        }
    }
}
