#ifndef CLUSTERPOINT_H
#define CLUSTERPOINT_H

//#include "mpicLib_global.h"

class ClusterPoint
{
public:
	enum {LEFT = 1, UP = 2, RIGHT = 4, DOWN = 8, ALL = 15};
	enum pointType {NONE, SEED, CLUSTER,
					FIRST_BOUNDARY, SECOND_BOUNDARY};

public:
    ClusterPoint();
	void initialize(int x, int y, int minx, int maxx, int miny, int maxy);

	unsigned char type() {return m_type;}
	void setType (unsigned char type) {m_type = type;}

	int x() {return m_x;}
	int y() {return m_y;}
	unsigned char value() {return m_value;}
	unsigned char checkDir() {return m_checkDir;}
	void setCheckDir (unsigned char checkDir) {m_checkDir = checkDir;}

	int index() {return m_index;}
	int leftIndex() {return m_leftIndex;}
	int upIndex() {return m_upIndex;}
	int rightIndex() {return m_rightIndex;}
	int downIndex() {return m_downIndex;}

	unsigned char leftValue() {return m_leftValue;}
	unsigned char upValue() {return m_upValue;}
	unsigned char rightValue() {return m_rightValue;}
	unsigned char downValue() {return m_downValue;}

	static void setImageWidth(unsigned char *image, int width);

private:
	unsigned char m_type;
	int m_x, m_y;
	int m_index;
	unsigned char m_value;
	unsigned char m_checkDir;

	int m_leftIndex;
	int m_upIndex;
	int m_rightIndex;
	int m_downIndex;

	unsigned char m_leftValue;
	unsigned char m_upValue;
	unsigned char m_rightValue;
	unsigned char m_downValue;

	// Share in all ClusterPoint
	static unsigned char *sm_image;
	static int sm_width;
};

#endif // CLUSTERPOINT_H
