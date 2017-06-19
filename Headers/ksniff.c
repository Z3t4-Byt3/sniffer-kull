#include <stdio.h>
#include <pcap/pcap.h>
#include <net/ethernet.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>
#include <netinet/ip_icmp.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int print_source_dest_address (char* source, char* dest) {
  if (strncmp (source, dest, INET_ADDRSTRLEN) != 0) {
    printf ("%s --> %s : ", source, dest);
    return 1;
  }
  else
    return -1;
}

void print_tcp_packet (const u_char *buffer, struct iphdr *iph) {

  unsigned short iphdrlen = (unsigned short) (iph-> ihl*4);

  struct tcphdr *tcph = (struct tcphdr *) (buffer + iphdrlen + 
      sizeof(struct ethhdr));

  printf ("%u --> %u : ", ntohs (tcph-> source), ntohs (tcph-> dest));

  int flagtcp = (unsigned int) tcph-> urg;
  if (flagtcp == 1)
    printf ("URG ");

  flagtcp = (unsigned int) tcph-> ack;
  if (flagtcp == 1)
    printf ("ACK ");

  flagtcp = (unsigned int) tcph-> psh;
  if (flagtcp == 1)
    printf ("PSH ");

  flagtcp = (unsigned int) tcph-> rst;
  if (flagtcp == 1)
    printf ("RST ");

  flagtcp = (unsigned int) tcph-> syn;
  if (flagtcp == 1)
    printf ("SYN ");

  flagtcp = (unsigned int) tcph-> fin;
  if (flagtcp == 1)
    printf ("FIN");

  printf ("\n");

}

void print_udp_packet (const u_char *buffer, struct iphdr *iph) {

  unsigned short iphdrlen = (unsigned short) (iph-> ihl*4);

  struct udphdr *udph = (struct udphdr *) (buffer + iphdrlen + 
      sizeof(struct ethhdr));

  printf ("%u --> %u\n", ntohs (udph-> source), ntohs (udph-> dest));

}

void print_icmp_packet (const u_char *buffer, struct iphdr *iph) {

  unsigned short iphdrlen = (unsigned short) (iph-> ihl*4);

  struct icmphdr *icmph = (struct icmphdr *) (buffer + iphdrlen + 
      sizeof(struct ethhdr));

  printf ("Type: %d\n", (unsigned int) (icmph-> type));

}

void print_ip_header (const u_char *buffer, struct iphdr *iph, 
    int protocolo) {

  struct sockaddr_in source, dest;
  int return_i;

  bzero (&source, sizeof(source));
  source.sin_addr.s_addr = iph-> saddr;
  bzero (&dest, sizeof(dest));
  dest.sin_addr.s_addr = iph-> daddr;

  struct in_addr ipAddr;

  char source_ip[INET_ADDRSTRLEN];
  char dest_ip[INET_ADDRSTRLEN];

  ipAddr = source.sin_addr;
  inet_ntop (AF_INET, &ipAddr, source_ip, INET_ADDRSTRLEN);
  ipAddr = dest.sin_addr;
  inet_ntop (AF_INET, &ipAddr, dest_ip, INET_ADDRSTRLEN);

  return_i = print_source_dest_address (source_ip, dest_ip);

  if (return_i > 0) {

    switch (protocolo) {
      case 1:
        printf ("[icmp] ");
        print_icmp_packet (buffer, iph);
        break;
      case 6:
        printf ("[tcp] ");
        print_tcp_packet (buffer, iph);
        break;
      case 17:
        printf ("[udp] ");
        print_udp_packet (buffer, iph);
        break;
      default:
        break;
    }

  }

}

void process_packet (u_char *args, const struct pcap_pkthdr *header,
    const u_char *buffer) {

  (void) args;

  struct iphdr *ipheader = (struct iphdr *) (buffer + sizeof(struct ethhdr));

  print_ip_header (buffer, ipheader, ipheader-> protocol);

  (void) header;

}

