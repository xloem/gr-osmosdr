/* -*- c++ -*- */
/*
 * Copyright 2018 Karl Semich <0xloem@gmail.com>
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
#ifndef INCLUDED_OSMOSDR_MESSAGES_H
#define INCLUDED_OSMOSDR_MESSAGES_H

#include <pmt/pmt.h>

namespace osmosdr {

const pmt::pmt_t CMD_PORT = pmt::mp("command");
const pmt::pmt_t CMD_CHAN_KEY = pmt::mp("chan");
const pmt::pmt_t CMD_GAIN_KEY = pmt::mp("gain");
const pmt::pmt_t CMD_FREQ_KEY = pmt::mp("freq");
const pmt::pmt_t CMD_RATE_KEY = pmt::mp("rate");
const pmt::pmt_t CMD_ANTENNA_KEY = pmt::mp("antenna");
const pmt::pmt_t CMD_BANDWIDTH_KEY = pmt::mp("bandwidth");

} /* namespace osmosdr */

#endif /* INCLUDED_OSMOSDR_MESSAGES_H */
