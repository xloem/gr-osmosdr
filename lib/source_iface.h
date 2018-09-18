/* -*- c++ -*- */
/*
 * Copyright 2012 Dimitri Stolnikov <horiz0n@gmx.net>
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

#ifndef OSMOSDR_SOURCE_IFACE_H
#define OSMOSDR_SOURCE_IFACE_H

#include <osmosdr/ranges.h>
#include <osmosdr/time_spec.h>
#include <gnuradio/basic_block.h>

#include "common_iface.h"

/*!
 * TODO: document
 *
 */
class source_iface : public common_iface
{
public:
  /*!
   * \brief seek file to \p seek_point relative to \p whence
   *
   * \param seek_point	sample offset in file
   * \param whence	one of SEEK_SET, SEEK_CUR, SEEK_END (man fseek)
   * \return true on success
   */
  virtual bool seek( long seek_point, int whence, size_t chan = 0 ) { return false; }

  /*!
   * Set the RX frontend DC correction mode.
   * The automatic correction subtracts out the long-run average.
   *
   * When disabled, the averaging option operation is reset.
   * Once in Manual mode, the average value will be held constant until
   * the user re-enables the automatic correction or overrides the
   * value by manually setting the offset.
   *
   * \param mode dc offset correction mode: 0 = Off, 1 = Manual, 2 = Automatic
   * \param chan the channel index 0 to N-1
   */
  virtual void set_dc_offset_mode( int mode, size_t chan = 0 ) { }

  /*!
   * Set the RX frontend IQ balance mode.
   *
   * \param mode iq balance correction mode: 0 = Off, 1 = Manual, 2 = Automatic
   * \param chan the channel index 0 to N-1
   */
  virtual void set_iq_balance_mode( int mode, size_t chan = 0 ) { }
};

#endif // OSMOSDR_SOURCE_IFACE_H
