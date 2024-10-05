#include "ChessPiece.h"
#include "math.h"
#include "bmp.h"

// class (static) variables representing the shared
// texture objects.
bool ChessPiece::TexturesInitialized(0);
GLubyte *ChessPiece::BlackTexture(0);
GLubyte *ChessPiece::WhiteTexture(0);
int ChessPiece::BlackTextureWidth(0);
int ChessPiece::WhiteTextureWidth(0);
GLuint ChessPiece::BlackTextureID(0);
GLuint ChessPiece::WhiteTextureID(0);

// This is only called once, loading the textures from
// the files and created texture objects for both
// white and black chess pieces.
void ChessPiece::SetUpSharedTextures()
{
    if (TexturesInitialized)
    {
        return;
    }
    char white[]="green.bmp", black[]="Granite.bmp";
    
    
    ChessPiece::loadTexture(white, WHITE);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glGenTextures(1, &WhiteTextureID);
    glBindTexture(GL_TEXTURE_2D, WhiteTextureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, WhiteTextureWidth, WhiteTextureWidth, 
                 0, GL_RGBA, GL_UNSIGNED_BYTE,
                 WhiteTexture);
    
    
    ChessPiece::loadTexture(black, BLACK);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glGenTextures(1, &BlackTextureID);
    glBindTexture(GL_TEXTURE_2D, BlackTextureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, BlackTextureWidth, BlackTextureWidth, 
                 0, GL_RGBA, GL_UNSIGNED_BYTE,
                 BlackTexture);
    
    TexturesInitialized = true;
}

void ChessPiece::loadTexture(char *file, int color)
{
    //char str[] ="wmarble.bmp";
    BMP *bmp = new BMP();
    bmp->readWithString(file);
    unsigned char *colorValues = bmp->getColorValues();
    
    // changed : added computation for textureWidth in case texture is not square
    int width = bmp->getWidth();
    int height = bmp->getHeight();
    if (height < width)
    {
        width = height;
    }
    if (color == WHITE)
    {
        WhiteTextureWidth = width;
    }
    else
    {
        BlackTextureWidth = width;
    }
    
    // changed: added malloc for texture
    GLubyte *texture = (GLubyte*) malloc(sizeof(GLubyte) * 4 * width * width);
    
    // changed :use textureWidth
    int i = 0;
    int j = 0;
    for (i = width - 1; i >= 0; --i) {
        for (j = 0; j < width; ++j) {
            // changed : use index variable 
            int index = i * 4 * width + 4 * j;
            texture[index] = (GLubyte) colorValues[(i * 3 * width) + j*3 + 0];
            //printf("red = %d\n", (int) texture[i][j][0]);
            texture[index + 1] = (GLubyte) colorValues[(i * 3 * width) + j*3 + 1];
            //printf("green = %d\n", (int) texture[i][j][1]);
            texture[index + 2] = (GLubyte) colorValues[(i * 3 * width) + j*3 + 2];
            //printf("blue = %d\n", (int) texture[i][j][2]);
            texture[index + 3] = (GLubyte) 255;
        }
    }
    if (color == WHITE)
    {
        WhiteTexture = texture;
    }
    else
    {
        BlackTexture = texture;
    }
}


ChessPiece::ChessPiece(Point position)
: Model(position), points(), texs(), norms()
{
    switch (detail)
    {
        case 0:
            nx = 4;
            ntheta = 4;
            break;
        case 1:
            nx = 10;
            ntheta = 10;
            break;
        case 2:
            nx = 25;//number of slices along x-direction
            ntheta = 15;//number of angular slices
            break;
        case 3:
            nx = 40;
            ntheta = 30;
            break;
        case 4:
            nx = 80;
            ntheta = 80;
            break;
        default:
            nx = 25;
            ntheta = 15;
    }
    
}


void ChessPiece::update(int elapsedTime, int deltaTime)
{
    if (_position.y < 0 || _position.y > 30)
    {
        _position.x = _initialPosition.x;
        _position.y = _initialPosition.y;
        _position.z = _initialPosition.z;
        _linearSpeedX = 0;
        _linearSpeedY = 0;
        _linearSpeedZ = 0;
    }
    Model::update(elapsedTime, deltaTime);
}

void ChessPiece::bump(Point direction)
{ 
    float speed = .04;
    float deltaX = _position.x - direction.x;
    float deltaZ = _position.z - direction.z;
    float theta = atan2(deltaZ, deltaX);
    if (theta < 0.0)
    {
        theta = 2.0 * M_PI + theta;
    }
    _linearSpeedX = speed * cos(theta); 
    _linearSpeedZ = speed * sin(theta);
}


float ChessPiece::polyint (GLfloat *points, float x, int N )
{
    float y;
    
    float num = 1.0, den = 1.0;
    float sum = 0.0;
    
    for ( int i = 0; i < N; ++i ) {
        num = den = 1.0;
        for ( int j = 0; j < N; ++j ) {
            if ( j == i ) continue;
            
            num = num * ( x - points[j*3] );             //x - xj
        }
        for ( int j = 0; j < N; ++j ) {
            if ( j == i ) continue;
            den = den * ( points[i*3] - points[j*3] );    //xi - xj
        }
        sum += num / den * points[(i*3) + 1];
    }
    y = sum;
    
    return y;
}

// Calculating the surface normals:
// The points are in a vector, and are rendered
// as quads, so every 4 points represents a single
// quad.  It is assumed that the quad is rendered
// counter-clockwise.  If the point are accessed
// in order as P1, P2, P3, P4, the we let a vector
// A = P3 - P2 and vector B = P1 - P2.  Then
// A x B will be pointing out of the surface.
// So A x B is calculated and then normalized.
// This normal is used for each of the 4 points
// of the quad, and vector points is indexed 4 positions
// at a time.
void ChessPiece::createSurfaceNormals()
{
    Point defaultNormal;
    defaultNormal.x = 0;
    defaultNormal.y = 0;
    defaultNormal.z = 1;
    // The container of points should already be filled at this time
    int numberOfPoints = points.size();
    int i;
    for (i = 0; i < numberOfPoints; i += 4)
    {
        // Calculation of the normal at p1
        
        Point p1 = points[i];
        Point p2 = points[i + 1];
        Point p3 = points[i + 2];
        
        Point end;  // The end point of the normal from p1
        Point A;
        A.x = p3.x - p2.x;
        A.y = p3.y - p2.y;
        A.z = p3.z - p2.z;
        Point B;
        B.x = p1.x - p2.x;
        B.y = p1.y - p2.y;
        B.z = p1.z - p2.z;
        
        // A x B
        end.x = A.y * B.z - B.y * A.z;
        end.y = B.x * A.z - A.x * B.z;
        end.z = A.x * B.y - B.x * A.y;
        
        float length = sqrt(end.x * end.x + end.y * end.y + end.z * end.z);
        
        Point normal;
        normal.x = end.x / length;
        normal.y = end.y / length;
        normal.z = end.z / length;
        
        norms.push_back(normal);
        norms.push_back(normal);
        norms.push_back(normal);
        norms.push_back(normal);
        //norms.push_back(defaultNormal);
         
    }
}

void ChessPiece::createTop()
{
    if (numberTopPoints == 0)
        return;
    startIndexOfTop = index;  // Value set here for reference elsewhere.
	int i, j;
	float x, y, z, r;                //current coordinates
	float x1, y1, z1, r1;            //next coordinates
	float theta;
	
	const float startx = topStartX, endx = topEndX;
	const float dx = (endx - startx) / nx;    //x step size
	const float dtheta = 2*M_PI / ntheta;        //angular step size
	
	x = startx;
	r = polyint( topControlPts, x, numberTopPoints);
	
	for ( i = 0; i < nx; ++i ) 
	{            //step through x
		theta = 0;
		x1 = x + dx;                //next x
		
		r1 = polyint( topControlPts, x1, numberTopPoints);        //next f(x)
		//draw the surface composed of quadrilaterals by sweeping theta
		for ( j = 0; j <= ntheta; ++j )
		{
			theta += dtheta;
			double cosa = cos( theta );
			double sina = sin ( theta );
			y = r * cosa;  y1 = r1 * cosa;    //current and next y
			z = r * sina;     z1 = r1 * sina;    //current and next z
			
			
            // The order in which the next two points are added
            // is important since this determines if it is a
            // back face or front face.
			
			TextureCoordinate s;
			s.u = ((float) i) / (float) nx;
			s.v = ((float) j) / (float) ntheta;
			texs.push_back(s);
			
			Point n2;
			n2.x = 0;
			n2.y = 0;
			n2.z = 1;
			//norms.push_back(n2);
			
			Point w;
			w.x = y1;
			w.y = -x1;
			w.z = z1;
			points.push_back(w);
            
            
			TextureCoordinate t;
			t.u = ((float) i) / (float) nx;
			t.v = ((float) j) / (float) ntheta;
			texs.push_back(t);
			
			Point n1;
			n1.x = 0;
			n1.y = 0;
			n1.z = 1;
			//norms.push_back(n1);
			
			Point v;
			v.x = y;
			v.y = -x;
			v.z = z;
			points.push_back(v);
			
			//forms quad with next pair of points with incremented theta value    
		}          
		x = x1;
		r = r1;    
	} //for i
}

void ChessPiece::createBase()
{
    int i, j;
    float x, y, z, r;                //current coordinates
    float x1, y1, z1, r1;            //next coordinates
    float theta;
    
    //const float startx = 6.0, endx = 14.7;
    const float startx = baseStartX, endx = baseEndX;
    const float dx = (endx - startx) / nx;    //x step size
    const float dtheta = 2*M_PI / ntheta;        //angular step size
    
    x = startx;
    r = polyint(baseControlPts, x, numberBasePoints);
    
    for ( i = 0; i < nx; ++i ) {            //step through x
        theta = 0;
        x1 = x + dx;                //next x
        r1 = polyint(baseControlPts, x1, numberBasePoints);        //next f(x)
        //draw the surface composed of quadrilaterals by sweeping theta
        for ( j = 0; j <= ntheta; ++j ) {
            theta += dtheta;
            double cosa = cos( theta );
            double sina = sin ( theta );
            y = r * cosa;  y1 = r1 * cosa;    //current and next y
            z = r * sina;     z1 = r1 * sina;    //current and next z
            
            // The order in which the next two points are added
            // is important since this determines if it is a
            // back face or front face.
            
            TextureCoordinate s;
            s.u = ((float) i) / (float) nx;
            s.v = ((float) j) / (float) ntheta;
            texs.push_back(s);
            
            Point n2;
            n2.x = 0;
            n2.y = 0;
            n2.z = 1;
            //norms.push_back(n2);
            
            Point r;
            r.x = y1;
            r.y = -x1;
            r.z = z1;
            points.push_back(r);
            
            
            TextureCoordinate t;
            t.u = ((float) i) / (float) nx;
            t.v = ((float) j) / (float) ntheta;
            texs.push_back(t);
            
            Point n1;
            n1.x = 0;
            n1.y = 0;
            n1.z = 1;
            //norms.push_back(n1);
            
            Point p;
            p.x = y;
            p.y = -x;
            p.z = z;
            points.push_back(p);
            
            //forms quad with next pair of points with incremented theta value    
        } 
        x = x1;
        r = r1;    
    } //for i
}
void ChessPiece::displayTop(void)
{   
    int i, j;
    
    for ( i = 0; i < nx; ++i ) 
    {            //step through x
        //draw the surface composed of quadrilaterals by sweeping theta
        if (_showWireFrame)
        {
            glBegin(GL_LINE_STRIP);
        }
        else
        {
            glBegin( GL_QUAD_STRIP );
        }
        for ( j = 0; j <= ntheta; ++j )
        {
            
            //edge from point at x to point at next x
            glTexCoord2f(texs[index].u, texs[index].v);
            glNormal3f(norms[index].x, norms[index].y, norms[index].z);
            glVertex3f (points[index].x, points[index].y, points[index].z);
            
            ++index;
            
            glTexCoord2f(texs[index].u, texs[index].v);
            glNormal3f(norms[index].x, norms[index].y, norms[index].z);
            glVertex3f (points[index].x, points[index].y, points[index].z);
            
            ++index;
            
            //forms quad with next pair of points with incremented theta value    
        }                  
        glEnd();
    } //for i
}

void ChessPiece::displayBase()
{
	index = 0;
	int i, j;
	
	
	for ( i = 0; i < nx; ++i ) {            //step through x
		
		if (_showWireFrame)
		{
			glBegin(GL_LINE_STRIP);
		}
		else
		{
			glBegin( GL_QUAD_STRIP );
		}
		for ( j = 0; j <= ntheta; ++j ) {
			
			//edge from point at x to point at next x
			glTexCoord2f(texs[index].u, texs[index].v);
			
			glNormal3f(norms[index].x, norms[index].y, norms[index].z);
			glVertex3f (points[index].x, points[index].y, points[index].z);
			++index;
			glTexCoord2f(texs[index].u, texs[index].v);
			glNormal3f(norms[index].x, norms[index].y, norms[index].z);
			glVertex3f (points[index].x, points[index].y, points[index].z);
			++index;
			
			//forms quad with next pair of points with incremented theta value    
		}                  
		glEnd();
	} //for i
}


void ChessPiece:: init()
{
    //loadTexture(str);
    //_radius = 5;
    _checkCollisions = true;
    _respondsToCollisions = true;
    createBase();
    createTop();
    createSurfaceNormals();
    _projectShadow = true;
    
    ChessPiece::SetUpSharedTextures();
    if (color == WHITE)
    {
        myTexture = WhiteTexture;
        myTextureWidth = WhiteTextureWidth;
        myTextureID = WhiteTextureID;
    }
    else
    {
        myTexture = BlackTexture;
        myTextureWidth = BlackTextureWidth;
        myTextureID = BlackTextureID;
    }
    
    // We want the seem to face away of the camera initially
    // for cosmetic purposes.
    if (color == WHITE)
    {
        _yaw = 180;
    }
}


void ChessPiece::doPreTransformations()
{
    glPushMatrix();
    glTranslatef(_position.x, _position.y + 7.0, _position.z);
    glRotatef(_roll, 0.0, 0.0, 1.0);
    glRotatef(_pitch, 1.0, 0.0, 0.0);
    glRotatef(_yaw, 0.0, 1.0, 0.0);
    glScalef(1.5, 1.5, 1.5);
}

void ChessPiece::draw()
{
    if (_showTextures)
    {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, myTextureID);
    }
    
    displayBase();
    if (topControlPts)
        displayTop();
    
    glDisable(GL_TEXTURE_2D);
    
}

void ChessPiece::drawProjectionShadow()
{    
    displayBase();
    if (topControlPts)
        displayTop();
}
