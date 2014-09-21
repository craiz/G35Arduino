using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.ComponentModel;
using Windows.UI.Xaml.Media;

namespace LightSimulator
{
    class LightBulb : INotifyPropertyChanged
    {
        private SolidColorBrush _brush;
        private UInt16 _color;

        public LightBulb()
        {
            _brush = new SolidColorBrush();
            BulbColor = 0x0000;
        }

        public SolidColorBrush BulbBrush
        {
            get { return _brush; }
        }

        public UInt16 BulbColor
        {
            get { return _color; }
            set
            {
                _color = value;

                // XRGB
                // R = bits 11-8
                // G = bits 7-4
                // B = bits 3-0

                byte r = (byte)((_color >> 8) & 0x0F);
                byte g = (byte)((_color >> 4) & 0x0F);
                byte b = (byte)(_color & 0x0F);
                Windows.UI.Color color;
                color.A = 0xFF;
                color.R = (byte)(r * 16);
                color.G = (byte)(g * 16);
                color.B = (byte)(b * 16);

                _brush.Color = color;

                RaisePropertyChanged("BulbBrush");
            }
        }

        public event PropertyChangedEventHandler PropertyChanged;
        protected void RaisePropertyChanged(string name)
        {
            if (PropertyChanged != null)
            {
                PropertyChanged(this, new PropertyChangedEventArgs(name));
            }
        }
    }
}
