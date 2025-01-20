#include <libc.h>
char s[128];                            // s: the current input string
u8 n[32], blk_left[32], max_left[128];  // n: lengths of broken input springs
u40 memo[4096];                         // 20,480 bytes of memoization cache

bool fits(u8 i, u8 k) {                 // Measures if a spring sequence of
  for(u8 num = n[k]; num--; ++i)        // length n[k] fits at position
    if (s[i] != '#' && s[i] != '?')     // s[i]...s[i+n[k]]
      return false;
  return s[i] != '#';                   // Must be delimited at end of sequence
}

u40 NW(u8 i, u8 k);                     // Memoized front of num_ways()

u40 num_ways(u8 i, u8 k) {              // Calc # of ways to fit blocks to input
  if (blk_left[k]>max_left[i]) return 0;// Global cut-off lookahead
  while(s[i] == '.') ++i;               // Skip past '.'s without recursing to
                                        // avoid stack overflow on the C64
  if (s[i] == '#')                      // If we see a '#', there is only one
    return fits(i,k)?NW(i+n[k]+1,k+1):0;// linear choice, either fits or won't.

  if (s[i] == '?') {                    // In case of '?', we have two choices:
    if (n[k] && fits(i, k))             // either root the next seq. at here, or
      return NW(i+n[k]+1, k+1)          // leave this ? empty. Recurse into both
           + NW(i+1,      k);           // choices.
    else return NW(i+1,k);              // If we can't root here, must skip this
  }
  return !n[k];                         // If at end of input string, must also
                                        // be at the end of the group array.
}

u40 NW(u8 i, u8 k) {                    // Same as num_ways(), but first gets
  u16 key = ((u16)i << 5) | k;          // the computation result from memo
  if (memo[key] == (u40)-1ll)           // cache, if it exists there.
    memo[key] = num_ways(i, k);
  return memo[key];
}

void dup5(char *s, u8 len) {            // Duplicates given string four more
  for(u8 i = 0; i < len; ++i)           // times in memory
    for(u8 j = 1; j < 5; ++j)
      s[j*len+i] = s[i];
  s[5*len] = 0;                         // Null terminate with a sentinel
}

int main() {
  BENCH();
  FILE *f = fopen("in12.txt", "r");
  u64 total = 0;
  while(fscanf(f, "%s", s) == 1) {      // Read input lines one at a time
    int len = strlen(s), num_blocks = 0;
    s[len++] = '?';                     // Join input 5 times with '?' between
    dup5(s,len);                        // Dup string to 5-fold
    s[5*len-1] = 0;                     // Remove last written '?' char

    max_left[5*len-1]=max_left[5*len]=0;// Fill in max_left array, which tells
    for(int i = 5*len-2; i >= 0; --i)   // for each index i of input string, how
      max_left[i] = max_left[i+1]       // many blocks can still possibly fit
              + (s[i]=='#'||s[i]=='?'); // to the rest of the string

    while(fscanf(f, "%d,", &len) == 1)  // Read input spring sequence lengths
      n[num_blocks++] = len;

    dup5((char*)n, num_blocks);         // Dup input spring lengths five-fold.
    blk_left[5*num_blocks] = 0;         
    for(int i=5*num_blocks-1;i>=0;--i){ // Fill blk_left array, which tells how
      blk_left[i] = blk_left[i+1]+n[i]; // many bad springs still need to fit.
    }
    memset(memo, 0xFF, sizeof(memo));   // Clear memo cache from previous run.
    total += NW(0, 0);                  // And calculate the result.
  }
  fclose(f);
  printf("Arrangements: %llu\n", total);
}
