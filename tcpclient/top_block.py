#!/usr/bin/env python
##################################################
# Gnuradio Python Flow Graph
# Title: Top Block
# Generated: Sat Nov  1 21:20:10 2014
##################################################

from gnuradio import analog
from gnuradio import audio
from gnuradio import blocks
from gnuradio import eng_notation
from gnuradio import filter
from gnuradio import gr
from gnuradio import wxgui
from gnuradio.eng_option import eng_option
from gnuradio.fft import window
from gnuradio.filter import firdes
from gnuradio.wxgui import fftsink2
from gnuradio.wxgui import forms
from grc_gnuradio import blks2 as grc_blks2
from grc_gnuradio import wxgui as grc_wxgui
from optparse import OptionParser
import wx

class top_block(grc_wxgui.top_block_gui):

    def __init__(self):
        grc_wxgui.top_block_gui.__init__(self, title="Top Block")
        _icon_path = "/usr/share/icons/hicolor/32x32/apps/gnuradio-grc.png"
        self.SetIcon(wx.Icon(_icon_path, wx.BITMAP_TYPE_ANY))

        ##################################################
        # Variables
        ##################################################
        self.center_freq_slider = center_freq_slider = 97.9e6
        self.channel_freq = channel_freq = center_freq_slider
        self.samp_rate = samp_rate = 2e6
        self.channel_width = channel_width = 200e3
        self.center_freq = center_freq = channel_freq
        self.audio_gain = audio_gain = 1

        ##################################################
        # Blocks
        ##################################################
        _samp_rate_sizer = wx.BoxSizer(wx.VERTICAL)
        self._samp_rate_text_box = forms.text_box(
        	parent=self.GetWin(),
        	sizer=_samp_rate_sizer,
        	value=self.samp_rate,
        	callback=self.set_samp_rate,
        	label='samp_rate',
        	converter=forms.float_converter(),
        	proportion=0,
        )
        self._samp_rate_slider = forms.slider(
        	parent=self.GetWin(),
        	sizer=_samp_rate_sizer,
        	value=self.samp_rate,
        	callback=self.set_samp_rate,
        	minimum=200000,
        	maximum=2.8e6,
        	num_steps=100,
        	style=wx.SL_HORIZONTAL,
        	cast=float,
        	proportion=1,
        )
        self.Add(_samp_rate_sizer)
        _audio_gain_sizer = wx.BoxSizer(wx.VERTICAL)
        self._audio_gain_text_box = forms.text_box(
        	parent=self.GetWin(),
        	sizer=_audio_gain_sizer,
        	value=self.audio_gain,
        	callback=self.set_audio_gain,
        	label='audio_gain',
        	converter=forms.float_converter(),
        	proportion=0,
        )
        self._audio_gain_slider = forms.slider(
        	parent=self.GetWin(),
        	sizer=_audio_gain_sizer,
        	value=self.audio_gain,
        	callback=self.set_audio_gain,
        	minimum=0,
        	maximum=10,
        	num_steps=100,
        	style=wx.SL_HORIZONTAL,
        	cast=float,
        	proportion=1,
        )
        self.Add(_audio_gain_sizer)
        self.wxgui_fftsink2_0 = fftsink2.fft_sink_c(
        	self.GetWin(),
        	baseband_freq=center_freq,
        	y_per_div=10,
        	y_divs=10,
        	ref_level=0,
        	ref_scale=2.0,
        	sample_rate=samp_rate,
        	fft_size=1024,
        	fft_rate=15,
        	average=True,
        	avg_alpha=None,
        	title="FFT Plot",
        	peak_hold=False,
        )
        self.Add(self.wxgui_fftsink2_0.win)
        self.rational_resampler_xxx_0 = filter.rational_resampler_ccc(
                interpolation=12,
                decimation=5,
                taps=None,
                fractional_bw=None,
        )
        self.low_pass_filter_0 = filter.fir_filter_ccf(int(samp_rate/channel_width), firdes.low_pass(
        	1, samp_rate, 75e3, 25e3, firdes.WIN_HAMMING, 6.76))
        _center_freq_slider_sizer = wx.BoxSizer(wx.VERTICAL)
        self._center_freq_slider_text_box = forms.text_box(
        	parent=self.GetWin(),
        	sizer=_center_freq_slider_sizer,
        	value=self.center_freq_slider,
        	callback=self.set_center_freq_slider,
        	label='center_freq_slider',
        	converter=forms.float_converter(),
        	proportion=0,
        )
        self._center_freq_slider_slider = forms.slider(
        	parent=self.GetWin(),
        	sizer=_center_freq_slider_sizer,
        	value=self.center_freq_slider,
        	callback=self.set_center_freq_slider,
        	minimum=88e6,
        	maximum=107e6,
        	num_steps=100,
        	style=wx.SL_HORIZONTAL,
        	cast=float,
        	proportion=1,
        )
        self.Add(_center_freq_slider_sizer)
        self.blocks_uchar_to_float_0 = blocks.uchar_to_float()
        self.blocks_multiply_const_vxx_0 = blocks.multiply_const_vff((audio_gain, ))
        self.blocks_float_to_complex_0 = blocks.float_to_complex(1)
        self.blocks_deinterleave_0 = blocks.deinterleave(gr.sizeof_float*1)
        self.blocks_add_const_vxx_0 = blocks.add_const_vff((-127, ))
        self.blks2_tcp_source_0 = grc_blks2.tcp_source(
        	itemsize=gr.sizeof_char*1,
        	addr="127.0.0.1",
        	port=1234,
        	server=False,
        )
        self.audio_sink_0 = audio.sink(48000, "", True)
        self.analog_wfm_rcv_0 = analog.wfm_rcv(
        	quad_rate=480e3,
        	audio_decimation=10,
        )

        ##################################################
        # Connections
        ##################################################
        self.connect((self.low_pass_filter_0, 0), (self.rational_resampler_xxx_0, 0))
        self.connect((self.rational_resampler_xxx_0, 0), (self.analog_wfm_rcv_0, 0))
        self.connect((self.analog_wfm_rcv_0, 0), (self.blocks_multiply_const_vxx_0, 0))
        self.connect((self.blocks_multiply_const_vxx_0, 0), (self.audio_sink_0, 0))
        self.connect((self.blocks_deinterleave_0, 0), (self.blocks_float_to_complex_0, 0))
        self.connect((self.blocks_deinterleave_0, 1), (self.blocks_float_to_complex_0, 1))
        self.connect((self.blks2_tcp_source_0, 0), (self.blocks_uchar_to_float_0, 0))
        self.connect((self.blocks_uchar_to_float_0, 0), (self.blocks_add_const_vxx_0, 0))
        self.connect((self.blocks_add_const_vxx_0, 0), (self.blocks_deinterleave_0, 0))
        self.connect((self.blocks_float_to_complex_0, 0), (self.low_pass_filter_0, 0))
        self.connect((self.blocks_float_to_complex_0, 0), (self.wxgui_fftsink2_0, 0))


# QT sink close method reimplementation

    def get_center_freq_slider(self):
        return self.center_freq_slider

    def set_center_freq_slider(self, center_freq_slider):
        self.center_freq_slider = center_freq_slider
        self.set_channel_freq(self.center_freq_slider)
        self._center_freq_slider_slider.set_value(self.center_freq_slider)
        self._center_freq_slider_text_box.set_value(self.center_freq_slider)

    def get_channel_freq(self):
        return self.channel_freq

    def set_channel_freq(self, channel_freq):
        self.channel_freq = channel_freq
        self.set_center_freq(self.channel_freq)

    def get_samp_rate(self):
        return self.samp_rate

    def set_samp_rate(self, samp_rate):
        self.samp_rate = samp_rate
        self._samp_rate_slider.set_value(self.samp_rate)
        self._samp_rate_text_box.set_value(self.samp_rate)
        self.low_pass_filter_0.set_taps(firdes.low_pass(1, self.samp_rate, 75e3, 25e3, firdes.WIN_HAMMING, 6.76))
        self.wxgui_fftsink2_0.set_sample_rate(self.samp_rate)

    def get_channel_width(self):
        return self.channel_width

    def set_channel_width(self, channel_width):
        self.channel_width = channel_width

    def get_center_freq(self):
        return self.center_freq

    def set_center_freq(self, center_freq):
        self.center_freq = center_freq
        self.wxgui_fftsink2_0.set_baseband_freq(self.center_freq)

    def get_audio_gain(self):
        return self.audio_gain

    def set_audio_gain(self, audio_gain):
        self.audio_gain = audio_gain
        self.blocks_multiply_const_vxx_0.set_k((self.audio_gain, ))
        self._audio_gain_slider.set_value(self.audio_gain)
        self._audio_gain_text_box.set_value(self.audio_gain)

if __name__ == '__main__':
    import ctypes
    import os
    if os.name == 'posix':
        try:
            x11 = ctypes.cdll.LoadLibrary('libX11.so')
            x11.XInitThreads()
        except:
            print "Warning: failed to XInitThreads()"
    parser = OptionParser(option_class=eng_option, usage="%prog: [options]")
    (options, args) = parser.parse_args()
    tb = top_block()
    tb.Start(True)
    tb.Wait()

