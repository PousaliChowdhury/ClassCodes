#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>


int main (int ac, char **av)
{
  int i, j, l, n, sid;
  struct sockaddr_in sad, cad;
  char sip_addr[32], msg[32], t;

  if (ac == 1)
    strcpy (sip_addr, "127.0.0.1");
  else
    strcpy (sip_addr, av[1]);
  sid = socket (AF_INET, SOCK_DGRAM, 0);
  sad.sin_family = AF_INET;
  sad.sin_addr.s_addr = inet_addr (sip_addr);
  sad.sin_port = htons(1234);
  bind (sid, (struct sockaddr *) &sad, sizeof (sad));
  l = sizeof (cad);
  while (1)
    {
      recvfrom (sid, (void *) msg, sizeof (msg), 0, (struct sockaddr *) &cad,
		&l);
      if (!strcmp (msg, "EXIT"))
	break;
      n = strlen (msg);
      // Reversing and resending the message
      for (i = 0, j = n - 1; i < j;
	   t = msg[i], msg[i] = msg[j], msg[j] = t, i++, j--);
      sendto (sid, (void *) msg, strlen (msg) + 1, 0,(struct sockaddr *) &cad, sizeof (cad));
    }
  return;
}
