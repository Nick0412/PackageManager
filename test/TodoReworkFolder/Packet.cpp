#include "Packet.hpp"

std::size_t Packet::id_counter_s = 1;

Packet::Packet(
    const Endpoint& source_endpoint,
    const Port& source_port, 
    const Endpoint& destination_endpoint, 
    const Port destination_port, 
    const ByteList& data)
: source_endpoint_{source_endpoint},
  destination_endpoint_{destination_endpoint},
  source_port_{source_port},
  destination_port_{destination_port},
  data_{data},
  id_{id_counter_s}
{
    id_counter_s++;
}
