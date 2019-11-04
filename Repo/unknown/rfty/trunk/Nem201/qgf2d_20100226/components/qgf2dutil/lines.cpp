#include "qgf2d/lines.h"
 
//Constructur
Lines::Lines() :
m_fLineThickness(1.0f),
m_bIsDisplayListCurrent(false)
{
	m_nDisplayListID = glGenLists(1);
}
 
//Destructor
Lines::~Lines()
{
	glDeleteLists(m_nDisplayListID, 1);
}
 
//Assignment operator
Lines& Lines::operator = (const Lines& that)
{
	if (this != &that)
	{
		m_vPoints = that.m_vPoints;
		m_vLineSegments = that.m_vLineSegments;
		m_bIsDisplayListCurrent = that.m_bIsDisplayListCurrent;
	}
 
	return *this;
}
 
//adds a point to the line shape
//returns an ID for that point
unsigned short Lines::AddPoint(const sf::Vector2f& v2fPointPosition)
{
	//search for a recycled point to use
	for (unsigned short i = 0; i < m_vPoints.size(); ++i)
	{
		if (!m_vPoints[i].bActive)
		{
			m_vPoints[i].v2fPoint = v2fPointPosition;
			m_vPoints[i].bActive = true;
			return i;
		}
	}
 
	//if no recycled point, add a new point
	m_vPoints.push_back(PointInfo(v2fPointPosition));
	return (unsigned short)(m_vPoints.size() - 1);
 
	//display commands are out-of-date now
	m_bIsDisplayListCurrent = false;
}
 
//adds a point to the line shape
//returns an ID for that point
unsigned short Lines::AddPoint(const float fXPosition, const float fYPosition)
{
	return AddPoint(sf::Vector2f(fXPosition, fYPosition));
}
 
//removes the passed point.
//Also removes any line segments that depended on that point
void Lines::RemovePoint(const unsigned short nPointID)
{
	//remove the point
	m_vPoints[nPointID].bActive = false;
 
	//remove all line segments referencing that point
	for (unsigned int i = 0; i < m_vLineSegments.size(); ++i)
	{
		if (m_vLineSegments[i].bActive && (m_vLineSegments[i].nPoint1 == nPointID || m_vLineSegments[i].nPoint2 == nPointID))
			RemoveLineSegment(i);
	}
 
	//display commands are out-of-date now
	m_bIsDisplayListCurrent = false;
}
 
//Moves the position of the point (Attached line segments automatically move appropriately)
void Lines::MovePoint(const unsigned short nPointID, const Vector2f& v2fNewPosition)
{
	m_vPoints[nPointID].v2fPoint = v2fNewPosition;
 
	//display commands are out-of-date now
	m_bIsDisplayListCurrent = false;
}
 
//Moves the position of the point (Attached line segments automatically move appropriately)
void Lines::MovePoint(const unsigned short nPointID, const float fNewPositionX, const float fNewPositionY)
{
	m_vPoints[nPointID].v2fPoint.x = fNewPositionX;
	m_vPoints[nPointID].v2fPoint.y = fNewPositionY;
 
	//display commands are out-of-date now
	m_bIsDisplayListCurrent = false;
}
 
//Adds a line segment that references 2 point IDs
//Does nothing if both point IDs don't exist and returns -1
//Object won't render if there isn't at least 1 line segment
//Returns an ID to the line segment
unsigned short Lines::AddLineSegment(const unsigned short nPoint1ID, const unsigned short nPoint2ID, const sf::Color& color)
{
	//search for a recycled line segment to use
	for (unsigned short i = 0; i < m_vLineSegments.size(); ++i)
	{
		if (!m_vLineSegments[i].bActive)
		{
			m_vLineSegments[i].nPoint1 = nPoint1ID;
			m_vLineSegments[i].nPoint2 = nPoint2ID;
			m_vLineSegments[i].color = color;
			m_vLineSegments[i].bActive = true;
			return (unsigned short)i;
		}
	}
 
	//if no recycled line segment, add a new one
	m_vLineSegments.push_back(LineSegmentInfo(nPoint1ID, nPoint2ID, color));
	return (unsigned short)(m_vLineSegments.size() - 1);
 
	//display commands are out-of-date now
	m_bIsDisplayListCurrent = false;
}
 
//removes the passed line segment.
//Also removes any no-longer used points if bRemoveOrphanPoints is true
void Lines::RemoveLineSegment(const unsigned short nLineSegmentID, bool bRemoveOrphanedPoints)
{
	//remove the line segment
	m_vLineSegments[nLineSegmentID].bActive = false;
 
	//remove all newly-orphaned points, if requested
	if (bRemoveOrphanedPoints)
	{
		//get the point IDs (we deactivated the segment above, but not change/delete values)
		unsigned short nPointID1 = m_vLineSegments[nLineSegmentID].nPoint1;
		unsigned short nPointID2 = m_vLineSegments[nLineSegmentID].nPoint2;
 
		//assume no reference until found
		bool bPoint1Referenced = false;
		bool bPoint2Referenced = false;
 
		//iterate through lines searching for references to both points
		for (unsigned int nLineIndex = 0; nLineIndex < m_vLineSegments.size(); ++nLineIndex)
		{
			if (!m_vLineSegments[nLineIndex].bActive)
				continue;
 
			if (m_vLineSegments[nLineIndex].nPoint1 == nPointID1 || m_vLineSegments[nLineIndex].nPoint2 == nPointID1)
				bPoint1Referenced = true;
			if (m_vLineSegments[nLineIndex].nPoint1 == nPointID2 || m_vLineSegments[nLineIndex].nPoint2 == nPointID2)
				bPoint2Referenced = true;
 
			//early out
			if (bPoint1Referenced && bPoint2Referenced)
				break;
		}
 
		//remove unreferenced points
		if (!bPoint1Referenced)
			m_vPoints[nPointID1].bActive = false;
		if (!bPoint2Referenced)
			m_vPoints[nPointID2].bActive = false;
	}
 
	//display commands are out-of-date now
	m_bIsDisplayListCurrent = false;
}
 
//sets the thickness of the passed line segment
void Lines::SetLineThickness(const float fLineThickness)
{
	m_fLineThickness = fLineThickness;
 
	//display commands are out-of-date now
	m_bIsDisplayListCurrent = false;
}
 
//sets the color of the passed line segment
void Lines::SetLineSegmentColor(const unsigned short nLineSegmentID, const sf::Color& color)
{
	m_vLineSegments[nLineSegmentID].color = color;
 
	//display commands are out-of-date now
	m_bIsDisplayListCurrent = false;
}
 
//returns the color of the passed line segment ID
const Color& Lines::GetLineSegmentColor(const unsigned short nLineSegmentID) const
{
	return m_vLineSegments[nLineSegmentID].color;
}
 
 
//gets the number of current line segments
int Lines::GetNumLineSegments()
{
	int nNumLineSegments = 0;
 
	//count each active line segment
	for (unsigned int i = 0; i < m_vLineSegments.size(); ++i)
	{
		if (m_vLineSegments[i].bActive)
			++nNumLineSegments;
	}
 
	return nNumLineSegments;
}
 
//removes all points and line segments
void Lines::Clear()
{
	unsigned int i;
	//deactivate points
	for (i = 0; i < m_vPoints.size(); ++i)
		m_vPoints[i].bActive = false;
	//deactivate line segments
	for (i = 0; i < m_vLineSegments.size(); ++i)
		m_vLineSegments[i].bActive = false;
 
	//display commands are out-of-date now
	m_bIsDisplayListCurrent = false;
}

 
//See Drawable::Render
void Lines::Render(RenderTarget& Window) const
{
	//if the display list is current, just run it
	if (m_bIsDisplayListCurrent)
	{
		glCallList(m_nDisplayListID);
		return;
	}
 
	// Make sure the shape has at least 1 line segment
	if (m_vLineSegments.size() < 1)
		return;
 
	//store all these generated commands in the display list
	glNewList(m_nDisplayListID, GL_COMPILE_AND_EXECUTE);
 
	// Shapes only use color, no texture
	glDisable(GL_TEXTURE_2D);
 
	// Draw the shape
	Color lineColor;
	Vector2f v2fLinePoint1, v2fLinePoint2;
 
	//set line thickness
	glLineWidth(m_fLineThickness);
	glBegin(GL_LINES);
	for (unsigned int i = 0; i < m_vLineSegments.size(); ++i)
	{
		if (!m_vLineSegments[i].bActive)
			continue;
 
		//set color
		lineColor = m_vLineSegments[i].color;
		glColor4ub(lineColor.r, lineColor.g, lineColor.b, lineColor.a);
		//pass line segment end-points
		v2fLinePoint1 = m_vPoints[m_vLineSegments[i].nPoint1].v2fPoint;
		v2fLinePoint2 = m_vPoints[m_vLineSegments[i].nPoint2].v2fPoint;
		glVertex2f(v2fLinePoint1.x, v2fLinePoint1.y);
		glVertex2f(v2fLinePoint2.x, v2fLinePoint2.y);
	}
	glEnd();
 
	glEndList();
 
	m_bIsDisplayListCurrent = true;
}

