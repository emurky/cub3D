#import <AppKit/NSScreen.h>
#include <math.h>

double	mlx_get_screen_size(int *width, int *height)
{
	CGFloat scale = [[NSScreen mainScreen] backingScaleFactor];
	NSRect disp = [[NSScreen mainScreen] frame];
	*height = (int)disp.size.height;
	*width = (int)disp.size.width;
	return (scale);
}
