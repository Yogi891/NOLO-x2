/*
A class that produces a fast-rendering shape drawn with display lists and GL_LNES.
Inherits from sf::Drawable, but some of those functions don't work, specifically SetColor since that's overridden per line-segment (default white).
To change the color, use the SetLineSegmentColor method.
To create a shape, use AddPoint to add all the vertices, catching the returned ID.  Then connect them with AddLineSegment.
 
This class meant to work with SFML (www.sfml-dev.org) and is released under the same liscence as SFML, zlib/png.
Class written by "Quasius"
*/
 
 
#ifndef DRAWABLE_LINE_SHAPE
#define DRAWABLE_LINE_SHAPE
 
#include <vector>
 
#include <SFML/Graphics.hpp>
 
using namespace std;
using namespace sf;
 
class Lines : public sf::Drawable
{
	//DEFINITIONS, STRUCTS, ETC
protected:
 
	struct LineSegmentInfo
	{
		unsigned short nPoint1, nPoint2;
		sf::Color color;
		//false if this line segment is in a recycled state
		bool bActive;
 
		LineSegmentInfo(const unsigned short nPoint1ID, const unsigned short nPoint2ID, const Color& lineColor = Color(255, 255, 255)) :
				bActive(true)
		{
			nPoint1 = nPoint1ID;
			nPoint2 = nPoint2ID;
			color = lineColor;
		}
	};
 
	struct PointInfo
	{
		Vector2f v2fPoint;
		//false if this point is in a recycled state
		bool bActive;
 
		PointInfo(const Vector2f& v2fLinePoint = Vector2f(0.0f, 0.0f)) :
			bActive(true)
		{
			v2fPoint = v2fLinePoint;
		}
	};
 
	//METHODS
public:
 
	//Constructur
	Lines();
 
	//Assignment operator
	Lines& operator = (const Lines& that);
 
	//Destructor
	~Lines();
 
	//adds a point to the line shape
	//returns an ID for that point
	unsigned short AddPoint(const Vector2f& v2fPointPosition);
 
	//adds a point to the line shape
	//returns an ID for that point
	unsigned short AddPoint(const float fXPosition, const float fYPosition);
 
	//removes the passed point.
	//Also removes any line segments that depended on that point
	void RemovePoint(const unsigned short nPointID);
 
	//Moves the position of the point (Attached line segments automatically move appropriately)
	void MovePoint(const unsigned short nPointID, const Vector2f& v2fNewPosition);
 
	//Moves the position of the point (Attached line segments automatically move appropriately)
	void MovePoint(const unsigned short nPointID, const float fNewPositionX, const float fNewPositionY);
 
	//Adds a line segment that references 2 point IDs
	//Does nothing if both point IDs don't exist and returns -1
	//Object won't render if there isn't at least 1 line segment
	//Returns an ID to the line segment
	unsigned short AddLineSegment(const unsigned short nPoint1ID, const unsigned short nPoint2ID, const Color& color = sf::Color(255, 255, 255));
 
	//removes the passed line segment.
	//Also removes any no-longer used points if bRemoveOrphanPoints is true
	void RemoveLineSegment(const unsigned short nLineSegmentID, bool bRemoveOrphanedPoints = true);
 
	//sets the thickness of the passed line segment
	void SetLineThickness(const float fLineThickness);
 
	//sets the color of the passed line segment
	void SetLineSegmentColor(const unsigned short nLineSegmentID, const Color& color);
 
	//returns the color of the passed line segment ID
	const Color& GetLineSegmentColor(const unsigned short nLineSegmentID) const;
 
	//gets the number of current line segments
	int GetNumLineSegments();
 
	//removes all points and line segments
	void Clear();
 
protected:
 
	//See Drawable::Render
	virtual void Render(RenderTarget& Window) const;
 
	//MEMBERS
protected:
 
	//All the points
	vector<PointInfo> m_vPoints;
	//All the line segments
	vector<LineSegmentInfo> m_vLineSegments;
	//the line thickness
	float m_fLineThickness;
	//Stores if the display list needs to be recompiled or not
	mutable bool m_bIsDisplayListCurrent;
	//the ID for the OpenGL display list
	int m_nDisplayListID;
};
 
#endif

