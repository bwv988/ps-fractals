/* draw_post.c  generate postscript to plot */
/* Written by Jon Squire 1/3/94               */

#include "draw_post.h"
#include <stdio.h>
static FILE *PSU;           /* post script output to filename.ps*/

void draw_post1(char *filename)
{
  PSU=fopen(filename,"w");
      if(!PSU) printf("no %s \n", filename);
  fprintf(PSU,"%%!PS-Adobe-1.0\n");
  
  fprintf(PSU,"/bdef {bind def} bind def \n");
  fprintf(PSU,"/ldef {load def} bdef \n");
  fprintf(PSU,"/n /newpath ldef \n");
  fprintf(PSU,"/c /closepath ldef \n");
  fprintf(PSU,"/l /lineto ldef \n");
  fprintf(PSU,"/m /moveto ldef \n");
  fprintf(PSU,"/s /setgray ldef \n");
  fprintf(PSU,"/f /fill ldef \n");
  fprintf(PSU,"/st /stroke ldef \n");
  fprintf(PSU,"/sw /setlinewidth ldef \n");
  fprintf(PSU,"newpath\n");
  fprintf(PSU,"/Times-Bold findfont\n");
  fprintf(PSU,"12 scalefont setfont\n");
  fprintf(PSU," 50 750 moveto (from file %s) show\n", filename);
  fprintf(PSU,"stroke\n");
} /* end draw_post1 */

/* draw line, thick=0.5 for thin, =1.0 for normal, =2.0 for thick */
void draw_post2(float x1, float y1, float x2, float y2, float thick)
{
/*  fprintf(PSU," %6.2f setlinewidth\n", thick);
  fprintf(PSU,"newpath\n");
  fprintf(PSU," %6.2f %6.2f moveto\n", x1, y1);
  fprintf(PSU," %6.2f %6.2f lineto\n", x2, y2);
  fprintf(PSU,"stroke\n");
*/
  fprintf(PSU,"%4.2f sw n %6.2f %6.2f m %6.2f %6.2f l st\n",
          thick, x1, y1, x2, y2);
} /* end draw_post2 */


/* gray shaded triangle, shade=0.1 dark, shade=0.99 light, else white */
void draw_post3(float x1, float y1, float x2, float y2,
                float x3, float y3, float shade)
{
  if (shade<=0.0 || shade>=1.0) return;
/*  fprintf(PSU,"newpath\n");
    fprintf(PSU," %6.2f %6.2f moveto\n", x1, y1);
    fprintf(PSU," %6.2f %6.2f lineto\n", x2, y2);
    fprintf(PSU," %6.2f %6.2f lineto\n", x3, y3);
    fprintf(PSU," %6.2f %6.2f lineto\n", x1, y1);
    fprintf(PSU,"closepath\n");
    fprintf(PSU," %7.5f setgray fill\n", shade);
    fprintf(PSU," 0.0 setgray\n");
*/
  fprintf(PSU,"n %6.2f %6.2f m %6.2f %6.2f l %6.2f %6.2f l %6.2f %6.2f l"
              " c %7.5f s f 0 s\n",
              x1, y1, x2, y2, x3, y3, x1, y1, shade);
} /* end draw_post3 */


/* outline triangle, thick=0.5 for thin, =1.0 for normal, =2.0 for thick */
void draw_post4(float x1, float y1, float x2, float y2,
                float x3, float y3, float thick)
{
/*  fprintf(PSU," %6.2f setlinewidth\n", thick);
    fprintf(PSU,"newpath\n");
    fprintf(PSU," %6.2f %6.2f moveto\n", x1, y1);
    fprintf(PSU," %6.2f %6.2f lineto\n", x2, y2);
    fprintf(PSU," %6.2f %6.2f lineto\n", x3, y3);
    fprintf(PSU," %6.2f %6.2f lineto\n", x1, y1);
    fprintf(PSU,"stroke\n");
*/
  fprintf(PSU,"%4.2f sw n %6.2f %6.2f m %6.2f %6.2f l %6.2f %6.2f l %6.2f %6.2f l st\n",
          thick, x1, y1, x2, y2, x3, y3, x1, y1);
} /* end draw_post4 */


/* simple text */
extern void draw_post5(float x1, float y1, char *text, int point)
{
  fprintf(PSU,"newpath\n");
  fprintf(PSU,"/Times-Bold findfont\n");
  fprintf(PSU,"%d scalefont setfont\n", point);
  fprintf(PSU," %6.2f %6.2f moveto (%s) show\n", x1, y1, text);
  fprintf(PSU,"stroke\n");
} /* end draw_post5 */



/* gray shaded rectangle, shade=0.1 dark, shade=0.99 light, else white */
/* units of printers point */
extern void draw_post6(int x1, int y1, int x2, int y2, float shade)
{
  if (shade<=0.0 || shade>=1.0) return;
/*  fprintf(PSU,"newpath\n");
    fprintf(PSU," %d %d moveto\n", x1, y1);
    fprintf(PSU," %d %d lineto\n", x2, y1);
    fprintf(PSU," %d %d lineto\n", x2, y2);
    fprintf(PSU," %d %d lineto\n", x1, y2);
    fprintf(PSU," %d %d lineto\n", x1, y1);
    fprintf(PSU,"closepath\n");
    fprintf(PSU," %7.5f setgray fill\n", shade);
    fprintf(PSU," 0.0 setgray\n");
*/
  fprintf(PSU,"n %d %d m %d %d l %d %d l %d %d l %d %d l c %7.5f s f 0 s\n",
          x1, y1, x2, y1, x2, y2, x1, y2, x1, y1, shade);
} /* end draw_post6 */


/* gray shaded square, shade=0.1 dark, shade=0.99 light, else white */
/*             1 point by 1 point */
void draw_post7(int x, int y, float shade)
{
  if (shade<=0.0 || shade>=1.0) return;
/*  fprintf(PSU,"newpath\n");
    fprintf(PSU," %d %d moveto\n", x,   y);
    fprintf(PSU," %d %d lineto\n", x+1, y);
    fprintf(PSU," %d %d lineto\n", x+1, y+1);
    fprintf(PSU," %d %d lineto\n", x,   y+1);
    fprintf(PSU," %d %d lineto\n", x,   y);
    fprintf(PSU,"closepath\n");
    fprintf(PSU," %7.5f setgray fill\n", shade);
    fprintf(PSU," 0.0 setgray\n");
*/
  fprintf(PSU,"n %d %d m %d %d l %d %d l %d %d l %d %d l c %7.5f s f 0 s\n",
          x, y, x+1, y, x+1, y+1, x, y+1, x, y, shade);
} /* end draw_post7 */


/* finish out file plotout.ps */
void draw_post99(void)
{
  fprintf(PSU,"showpage\n");
  fclose(PSU);
} /* end draw_post99 */


/* gray shaded polygon, shade=0.1 dark, shade=0.99 light, else white */
void draw_post98(float shade, XPoint ppts[], int npts)
{
  int i;
  if (shade<=0.0 || shade>=1.0) return;
  fprintf(PSU,"newpath\n");
  fprintf(PSU," %6.2f %6.2f moveto\n", 0.9*((float)ppts[0].x-100.0),
                                       0.9*(float)(600-ppts[0].y));
  for (i=1; i<npts; i++)
  {
    fprintf(PSU," %6.2f %6.2f lineto\n", 0.9*((float)ppts[i].x-100.0),
                                         0.9*(float)(600-ppts[i].y));
  }
  fprintf(PSU,"closepath\n");
  fprintf(PSU," %7.5f setgray fill\n", shade);
  fprintf(PSU," 0.0 setgray\n");
} /* end draw_post98  only one needing an X Windows type as of now */

