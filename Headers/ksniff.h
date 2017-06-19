#ifndef KSNIFF_H
#define KSNIFF_H

#include <pcap/pcap.h>
#include <netinet/ip.h>

void process_packet (u_char *args, const struct pcap_pkthdr *header, 
    const u_char *buffer);

int print_source_dest_address (char* source, char* dest);
void print_ip_header (const u_char *buffer, struct iphdr *iph, 
    int protocolo);

void print_tcp_packet (const u_char *buffer, struct iphdr *iph);
void print_udp_packet (const u_char *buffer, struct iphdr *iph);
void print_icmp_packet (const u_char *buffer, struct iphdr *iph);

#endif

