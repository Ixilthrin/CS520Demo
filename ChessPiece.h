#ifndef __CHESSPIECE_H__
#define __CHESSPIECE_H__

#include "main.h"
#include "Model.h"
#include <vector>

class ChessPiece : public Model
{
    public:
        enum {
            WHITE,
            BLACK
        };
protected:
    int color;
    int nx;//number of slices along x-direction
    int ntheta;//number of angular slices
    GLfloat *baseControlPts;
    GLfloat *topControlPts;
    int numberBasePoints;
    int numberTopPoints;
    int index;  // index into points, texs, and norms.
    int startIndexOfTop;  // for points, texs, and norms, this is the 
    // beginning of the top.
    vector<Point> points;
    vector<TextureCoordinate> texs;
    vector<Point> norms;
    float baseStartX;
    float baseEndX;
    float topStartX;
    float topEndX;
    GLubyte *myTexture;
    int myTextureWidth;
    GLuint myTextureID;
    
    static bool TexturesInitialized;
    static int BlackTextureWidth;
    static int WhiteTextureWidth;
    static GLuint BlackTextureID;
    static GLuint WhiteTextureID;
    static GLubyte *BlackTexture;
    static GLubyte *WhiteTexture;
    static void SetUpSharedTextures();
    static void loadTexture(char *file, int color);
public:
    ChessPiece(Point position);
    virtual ~ChessPiece() {}
    virtual void init();
    virtual void doPreTransformations();
    virtual void draw();
    void drawProjectionShadow();
    virtual void update(int elapsedTime, int deltaTime);
    virtual void bump(Point direction);
    float polyint(GLfloat *ctrlPoints, float x, int N );
    void createSurfaceNormals();
    void createBase();
    void displayBase();
    void createTop();
    void displayTop(void);
};

#endif
