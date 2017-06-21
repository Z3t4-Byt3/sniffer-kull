#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pcap/pcap.h>
#include <locale.h>

#include "../Headers/kcolor.h"
#include "../Headers/ksniff.h"

int main (int argc, char *argv[]) {

  setlocale (LC_ALL, "");

  if (argc != 2 || getuid() != 0)
    print_error (" Uso: sudo ./sniffer <device>");

  pcap_t *handle;
  char errbuf[PCAP_ERRBUF_SIZE];

  handle = pcap_open_live (argv[1], 65536, 1, 0, errbuf);
  if (handle == NULL) {
    fprintf (stderr, "[-] Erro ao tentar abrir %s: %s\n", argv[1], errbuf);
    exit (EXIT_FAILURE);
  }

  pcap_loop (handle, -1, process_packet, NULL);

  return 0;

}

