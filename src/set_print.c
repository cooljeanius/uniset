#include "set.h"

void
set_print(FILE *f, struct set *x)
{
    struct range *xp = x->r, *xe = x->r + x->length;
    for (; xp != xe; ++xp) {
        if (xp->first == xp->last)
            fprintf(f, "%x\n", xp->first);
        else
            fprintf(f, "%x..%x\n", xp->first, xp->last);
    }
}

static void
set_print_n(FILE *f, struct set *x, const char *format, unsigned int mask)
{
    unsigned int ranges[17][2];
    unsigned int pos, plane, fr, la, pf, pl;
    struct range *xs = x->r, *xe = x->r + x->length, *xp;
    xp = xs;
    pos = 0;
    for (plane = 0; plane < 17; ++plane) {
        if (xp == xe || (xp->first >> 16) > plane) {
            ranges[plane][0] = 0;
            ranges[plane][1] = 0;
        } else {
            ranges[plane][0] = pos;
            while (xp != xe && (xp->last >> 16) == plane) {
                pos++;
                xp++;
            }
            if (xp != xe && (xp->first >> 16) <= plane)
                pos++;
            ranges[plane][1] = pos;
        }
    }
    for (plane = 0; plane < 17; ++plane) {
        if (plane) fputs(",\n", f);
        fprintf(f, "{ /* plane */ %u, %u }", ranges[plane][0], ranges[plane][1]);
    }
    for (xp = xs; xp != xe; ++xp) {
        if (((xp->first ^ xp->last) >> 16) == 0) {
            fprintf(f, format, xp->first & mask, xp->last & mask);
        } else {
            pf = xp->first >> 16;
            pl = xp->last >> 16;
            for (plane = pf; plane <= pl; ++plane) {
                fr = plane == pf ? xp->first : 0;
                la = plane == pl ? xp->last : 0;
                fprintf(f, format, fr & mask, la & mask);
            }
        }
    }
    putc('\n', f);
}

void
set_print16(FILE *f, struct set *x)
{
    set_print_n(f, x, ",\n{ %u, %u }", 0xFFFF);
}

void
set_print32(FILE *f, struct set *x)
{
    set_print_n(f, x, ",\n{ 0x%04X, 0x%04X }", 0xFFFFFFFF);
}
