/*
 * Copyright (C) 2010 Richard Membarth <richard.membarth@cs.fau.de>
 *
 * Read/Write pgm files
 */

#ifndef __PGM_IMAGE_H__
#define __PGM_IMAGE_H__

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

/*************************************************************************
 * read pgm file in GIMP pgm ascii format from hard disk                 *
 *************************************************************************/
short int *read_image(int *width, int *height, const char *filename) {
    int x, y, max;
    int mincolor = 255, maxcolor = 0;
    int tmp;
    char buf[1024];
    char *ret;
    FILE *fp;
    short int *img;

    fp = fopen(filename, "rb");
    if (fp == NULL) {
        fprintf(stderr, "cannot open %s for reading %s", filename, strerror(errno));
        exit(EXIT_FAILURE);
    }

    /* first line = image format */
    ret = fgets(buf, sizeof(buf), fp);
    if (!ret) {
        fprintf(stderr, "read_image: ret == NULL\n");
        exit(EXIT_FAILURE);
    } else {
        buf[strlen(buf)-1] = '\0';
        if (!strcasecmp(buf, "P2")) fprintf(stderr, "read_image(%s): buf='%s'\n", filename, buf);
        else {
            fprintf(stderr, "ERROR: image not in ASCII (P2) PGM format: '%s'!\n", buf);
            exit(EXIT_FAILURE);
        }
    }
    /* second line = comment */
    ret = fgets(buf, sizeof(buf), fp);
    if (!ret) {
        fprintf(stderr, "read_image: ret == NULL\n");
        exit(EXIT_FAILURE);
    } else {
        buf[strlen(buf)-1] = '\0';
        if (buf[0] == '#') fprintf(stderr, "read_image(%s): buf='%s'\n", filename, buf);
        else {
            fprintf(stderr, "ERROR: comment expected in second line!\n");
            exit(EXIT_FAILURE);
        }
    }
    /* third line = width and height of image */
    ret = fgets(buf, sizeof(buf), fp);
    if (!ret) {
        fprintf(stderr, "read_image: ret == NULL\n");
        exit(EXIT_FAILURE);
    } else {
        buf[strlen(buf)-1] = '\0';
        if ((tmp=sscanf(buf, "%u %u", width, height)) != 2) {
            fprintf(stderr, "ERROR: can not parse buf='%s': %d %s\n", buf, tmp, strerror(errno));
            exit(EXIT_FAILURE);
        } else {
            fprintf(stderr, "read_image(%s): buf='%s'\n", filename, buf);
        }
    }
    /* forth line = max. value for intensity */
    ret = fgets(buf, sizeof(buf), fp);
    if (!ret) {
        fprintf(stderr, "read_image: ret == NULL\n");
        exit(EXIT_FAILURE);
    } else {
        buf[strlen(buf)-1] = '\0';
        if ((tmp=sscanf(buf, "%u", &max)) != 1) {
            fprintf(stderr, "ERROR: can not parse buf='%s': %d %s\n", buf, tmp, strerror(errno));
            exit(EXIT_FAILURE);
        } else {
            fprintf(stderr, "read_image(%s): buf='%s'\n", filename, buf);
        }
    }
    img = (short int *)malloc((*width**height) * sizeof(short int));

    for (y=0; y<*height; y++) {
        for (x=0; x<*width; x++) {
            ret = fgets(buf, sizeof(buf), fp);
            if (!ret) {
                fprintf(stderr, "read_image: ret == NULL\n");
                exit(EXIT_FAILURE);
            } else {
                buf[strlen(buf)-1] = '\0';
                if (sscanf(buf, "%d", &tmp) != 1) {
                    fprintf(stderr, "can not parse buf='%s'\n", buf);
                    exit(EXIT_FAILURE);
                }
                if (tmp > maxcolor) {
                    maxcolor = tmp;
                }
                if (tmp < mincolor) {
                    mincolor = tmp;
                }
                img[y**width + x] = (short int) tmp;
            }
        }
    }
    fprintf(stderr, "read_image(%s): mincolor=%d, maxcolor=%d\n", filename, mincolor, maxcolor);

    fclose(fp);
    return img;
}


/*************************************************************************
 * write pgm file in GIMP pgm ascii format to hard disk                  *
 *************************************************************************/
void write_image(short int *img, int width, int height, const char *filename) {
    int x, y;
    FILE *fp;
    int mincolor = 255, maxcolor = 0, offset = 0, tmp;

    fp = fopen(filename, "wb");
    if (fp == NULL) {
        fprintf(stderr, "cannot open %s for writing %s", filename, strerror(errno));
        exit(EXIT_FAILURE);
    }

    for (y=0; y<height; y++) {
        for (x=0; x<width; x++) {
            tmp = (int) img[y*width + x];
            if (tmp > maxcolor) {
                maxcolor = tmp;
            }
            if (tmp < mincolor) {
                mincolor = tmp;
            }
        }
    }

    offset = (mincolor < 0) ? -mincolor : 0;
    fprintf(stderr, "write_image(%s): mincolor=%d, maxcolor=%d, offset=%d -> %d..%d\n", filename, mincolor, maxcolor, offset, mincolor+offset, maxcolor+offset);
    fprintf(fp, "P2\n");
    fprintf(fp, "# bla\n");
    fprintf(fp, "%u %u\n", width, height);
    fprintf(fp, "%d\n", maxcolor+offset);
    for (y=0; y<height; y++) {
        for (x=0; x<width; x++) {
            //fprintf(fp, "%d\n", abs((int) img[y*width + x] + offset));
            fprintf(fp, "%d\n", offset + (int) img[y*width + x]);
        }
    }

    fclose(fp);
}

#endif /* __PGM_IMAGE_H__ */

