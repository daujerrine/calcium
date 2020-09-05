#ifndef _CA_DEBUG_H
#define _CA_DEBUG_H
#define DEBUG_TOGGLE

#ifdef DEBUG_TOGGLE
    #define CA_DBG_PLN printf("At: %s, ln: %d\n", __FILE__, __LINE__);
#else
    #define CA_DBG_PLN
#endif

#endif
