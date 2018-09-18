/* -*- c++ -*- */
/*
 * Copyright 2018 Karl Semich <0xloem@gmail.com>
 *
 * This file is part of GNU Radio
 *
 * GNU Radio is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * GNU Radio is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with GNU Radio; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifndef INCLUDED_DEV_CONTROL_H
#define INCLUDED_DEV_CONTROL_H

#include <gnuradio/hier_block2.h>
#include <gnuradio/block.h>

#include <osmosdr/messages.h>

#include "common_iface.h"

class dev_manager;

/*
 * We use boost::shared_ptr's instead of raw pointers for all access
 * to gr::blocks (and many other data structures).  The shared_ptr gets
 * us transparent reference counting, which greatly simplifies storage
 * management issues.  This is especially helpful in our hybrid
 * C++ / Python system.
 *
 * See http://www.boost.org/libs/smart_ptr/smart_ptr.htm
 *
 * As a convention, the _sptr suffix indicates a boost::shared_ptr
 */
typedef boost::shared_ptr<dev_manager> dev_manager_sptr;

/*!
 * \brief Return a shared_ptr to a new instance of dev_manager.
 *
 * To avoid accidental use of raw pointers, dev_manager's
 * constructor is private. make_dev_manager is the public
 * interface for creating new instances.
 */
dev_manager_sptr make_dev_manager ( gr::hier_block2_sptr outer );

/*!
 * \brief Manages a set of osmosdr devices.
 * \ingroup block
 *
 */
class dev_manager : public gr::block
{
private:
  // The friend declaration allows make_dev_manager to
  // access the private constructor.

  friend dev_manager_sptr make_dev_manager ( gr::hier_block2_sptr outer );

  /*!
   * \brief Manages a set of osmosdr devices.
   */
  dev_manager ( gr::hier_block2_sptr outer );    // private constructor

public:
  int general_work( int noutput_items,
                    gr_vector_int &ninput_items,
                    gr_vector_const_void_star &input_items,
                    gr_vector_void_star &output_items );

  void add_device( gr::basic_block_sptr block, common_iface *iface ); // add a device driver block to be managed
  size_t get_num_mboards() const;
  size_t get_mboard_for_channel( size_t chan ) const;
  bool is_sink( size_t mboard = 0 ) const;
  gr::basic_block_sptr get_block( size_t mboard ) const;
  common_iface * get_iface( size_t mboard ) const;
  size_t get_mboard_channel( size_t mboard ) const;

  size_t get_num_channels();

  bool seek( long seek_point, int whence, size_t chan);

  osmosdr::meta_range_t get_sample_rates( void );
  double set_sample_rate( double rate );
  double get_sample_rate( void );

  osmosdr::freq_range_t get_freq_range( size_t chan );
  double set_center_freq( double freq, size_t chan );
  double get_center_freq( size_t chan );
  double set_freq_corr( double ppm, size_t chan );
  double get_freq_corr( size_t chan );

  std::vector<std::string> get_gain_names( size_t chan );
  osmosdr::gain_range_t get_gain_range( size_t chan );
  osmosdr::gain_range_t get_gain_range( const std::string & name, size_t chan );
  bool set_gain_mode( bool automatic, size_t chan );
  bool get_gain_mode( size_t chan );
  double set_gain( double gain, size_t chan );
  double set_gain( double gain, const std::string & name, size_t chan );
  double get_gain( size_t chan );
  double get_gain( const std::string & name, size_t chan );

  double set_if_gain( double gain, size_t chan );
  double set_bb_gain( double gain, size_t chan );

  std::vector< std::string > get_antennas( size_t chan );
  std::string set_antenna( const std::string & antenna, size_t chan );
  std::string get_antenna( size_t chan );

  void set_dc_offset_mode( int mode, size_t chan );
  void set_dc_offset( const std::complex<double> &offset, size_t chan );

  void set_iq_balance_mode( int mode, size_t chan );
  void set_iq_balance( const std::complex<double> &balance, size_t chan );

  double set_bandwidth( double bandwidth, size_t chan );
  double get_bandwidth( size_t chan );
  osmosdr::freq_range_t get_bandwidth_range( size_t chan );

  void set_time_source(const std::string &source, const size_t mboard = 0);
  std::string get_time_source(const size_t mboard);
  std::vector<std::string> get_time_sources(const size_t mboard);
  void set_clock_source(const std::string &source, const size_t mboard = 0);
  std::string get_clock_source(const size_t mboard);
  std::vector<std::string> get_clock_sources(const size_t mboard);
  double get_clock_rate(size_t mboard = 0);
  void set_clock_rate(double rate, size_t mboard = 0);
  ::osmosdr::time_spec_t get_time_now(size_t mboard = 0);
  ::osmosdr::time_spec_t get_time_last_pps(size_t mboard = 0);
  void set_time_now(const ::osmosdr::time_spec_t &time_spec, size_t mboard = 0);
  void set_time_next_pps(const ::osmosdr::time_spec_t &time_spec);
  void set_time_unknown_pps(const ::osmosdr::time_spec_t &time_spec);

private:
  void msg_handler_command(pmt::pmt_t msg);
  void exec_msg_cmd(const pmt::pmt_t &cmd, const pmt::pmt_t &val, size_t chan);

  struct dev_t {
    common_iface * dev;
    gr::basic_block_sptr block;
    size_t chan;
  };

  std::vector< dev_t > _devs;
  std::vector< size_t > _chandevs;
  gr::hier_block2_sptr _outer;
  size_t _channels;

  /* cache to prevent multiple device calls with the same value coming from grc */
  double _sample_rate;
  std::map< size_t, double > _center_freq;
  std::map< size_t, double > _freq_corr;
  std::map< size_t, bool > _gain_mode;
  std::map< size_t, double > _gain;
  std::map< size_t, double > _if_gain;
  std::map< size_t, double > _bb_gain;
  std::map< size_t, std::string > _antenna;
#ifdef HAVE_IQBALANCE
  std::vector< gr::iqbalance::fix_cc * > _iq_fix;
  std::vector< gr::iqbalance::optimize_c * > _iq_opt;
  std::map< size_t, std::pair<float, float> > _vals;
#endif
  std::map< size_t, double > _bandwidth;
};

#endif /* INCLUDED_DEV_CONTROL_H */
