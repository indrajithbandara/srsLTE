  /**
 *
 * \section COPYRIGHT
 *
 * Copyright 2013-2014 The srsLTE Developers. See the
 * COPYRIGHT file at the top-level directory of this distribution.
 *
 * \section LICENSE
 *
 * This file is part of the srsLTE library.
 *
 * srsLTE is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, either version 3 of
 * the License, or (at your option) any later version.
 *
 * srsLTE is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * A copy of the GNU Lesser General Public License can be found in
 * the LICENSE file in the top-level directory of this distribution
 * and at http://www.gnu.org/licenses/.
 *
 */

#include "srslte/srslte.h"
#include "srslte/ue_itf/queue.h"
#include "srslte/ue_itf/sched_grant.h"
#include "srslte/ue_itf/params.h"

#ifndef UEULBUFFER_H
#define UEULBUFFER_H


namespace srslte {
namespace ue {
  
  /* Uplink scheduling assignment. The MAC instructs the PHY to prepare an UL packet (PUSCH or PUCCH) 
   * for transmission. The MAC must call generate_pusch() to set the packet ready for transmission
   */
  class SRSLTE_API ul_buffer : public queue::element {

  public: 
    bool     init_cell(srslte_cell_t cell, params *params_db);
    void     free_cell();
    void     set_tti(uint32_t tti);
    void     set_current_tx_nb(uint32_t current_tx_nb);
    bool     generate_pusch(sched_grant pusch_grant, uint8_t *payload, srslte_uci_data_t uci_data);    
    bool     generate_pucch(srslte_uci_data_t uci_data);
    bool     send_packet(void *radio_handler, srslte_timestamp_t rx_time);

  private: 
    params        *params_db; 
    srslte_cell_t  cell; 
    srslte_ue_ul_t ue_ul; 
    bool           signal_generated; 
    bool           cell_initiated; 
    cf_t*          signal_buffer;
    uint32_t       tti; 
    uint32_t       current_tx_nb; 
  };

}
}

#endif