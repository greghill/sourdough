#ifndef CONTROLLER_HH
#define CONTROLLER_HH

#include <cstdint>
#include <list>

/* Congestion controller interface */

class Controller
{
private:
  const double delay_window_delta_;
  const double delay_threshold_;
  const double loss_window_delta_;

  double the_window_size;
  double skewed_lowest_owt;
  double lowest_rtt;
  std::list< std::pair<uint64_t, uint64_t> > datagram_list_;

public:
  /* Public interface for the congestion controller */
  /* You can change these if you prefer, but will need to change
     the call site as well (in sender.cc) */

  /* Default constructor */
  Controller( const double delay_window_delta, const double delay_threshold, const double loss_window_delta );

  /* Get current window size, in datagrams */
  unsigned int window_size( void );

  /* A datagram was sent */
  void datagram_was_sent( const uint64_t sequence_number,
			  const uint64_t send_timestamp );

  /* An ack was received */
  void ack_received( const uint64_t sequence_number_acked,
		     const uint64_t send_timestamp_acked,
		     const uint64_t recv_timestamp_acked,
		     const uint64_t timestamp_ack_received );

  /* How long to wait (in milliseconds) if there are no acks
     before sending one more datagram */
  unsigned int timeout_ms( void );
};

#endif
