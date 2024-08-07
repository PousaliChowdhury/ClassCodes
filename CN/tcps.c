#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

int
main (int ac, char **av)
{
  int i, j, l, n, sid, cid;
  struct sockaddr_in sad, cad;
  char sip_addr[32], msg[32], t;

  if (ac == 1)
    strcpy (sip_addr, "127.0.0.1");
  else
    strcpy (sip_addr, av[1]);
  sid = socket (AF_INET, SOCK_STREAM, 0);
  sad.sin_family = AF_INET;
  sad.sin_addr.s_addr = inet_addr (sip_addr);
  sad.sin_port = htons(1234);
  bind (sid, (struct sockaddr *) &sad, sizeof (sad));
  listen (sid, 1);
  l = sizeof (cad);
  cid = accept (sid, (struct sockaddr *) &cad, &l);
  while (1)
    {
      n = read (cid, (void *) msg, sizeof (msg));
      msg[n] = 0;
      if (!strcmp (msg, "EXIT"))
	break;
      // Reversing and resending the message
      for (i = 0, j = n - 1; i < j;
	   t = msg[i], msg[i] = msg[j], msg[j] = t, i++, j--);
      write (cid, (void *) msg, strlen (msg));
    }
  return;
}
