#ifndef MACROS_H
#define MACROS_H

#define foreach(item, array) \
    for(int keep = 1, \
            count = 0,\
            size = sizeof (array) / sizeof *(array); \
        keep && count != size; \
        keep = !keep, count++) \
      for(item = (array) + count; keep; keep = !keep)
      
#define len(array) (sizeof (array) / sizeof *(array))

#endif // MACROS_H