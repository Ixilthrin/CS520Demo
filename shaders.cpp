#include "shaders.h"

ShaderObjects::~ShaderObjects()
{
}


int readShaderSource(char *fileName, GLchar **shaderCode, ShaderObjects &shader)
{
    // Allocate memory to hold the source of our shaders.
    FILE *fp;
    int count, pos, shaderSize;
    
    fp = fopen( fileName, "r");
    if ( !fp )
        return 0;
    
    pos = (int) ftell ( fp );
    fseek ( fp, 0, SEEK_END );            //move to end
    shaderSize = ( int ) ftell ( fp ) - pos;    //calculates file size    
    fseek ( fp, 0, SEEK_SET );             //rewind to beginning
    
    if ( shaderSize <= 0 ){
        printf("Shader %s empty\n", fileName);
        return 0;
    }
    
    *shaderCode = (GLchar *) malloc( shaderSize + 1);
    
    // Read the source code
    
    count = (int) fread(*shaderCode, 1, shaderSize, fp);
    (*shaderCode)[count] = '\0';
    
    if (ferror(fp))
        count = 0;
    
    fclose(fp);
    
    return 1;
}


//  public 
int installShaders(const GLchar *vertex, const GLchar *fragment, ShaderObjects &shader)
{
    GLint vertCompiled = 1;
    GLint fragCompiled = 1;  // status values
    GLint linked;
    
    // Create a vertex shader object and a fragment shader object
    if (vertex)
    {
        shader.vertexShaderObject = glCreateShader(GL_VERTEX_SHADER);
        // Load source code strings into shaders, compile and link
        glShaderSource(shader.vertexShaderObject, 1, &vertex, NULL);
        glCompileShader(shader.vertexShaderObject);
        glGetShaderiv(shader.vertexShaderObject, GL_COMPILE_STATUS, &vertCompiled);
        // If these values are both 1, compilation was successful
        printf("vertCompiled = %d\n", vertCompiled);
    }
    if (fragment)
    {
        shader.fragmentShaderObject = glCreateShader(GL_FRAGMENT_SHADER);
        // Load source code strings into shaders, compile and link
        glShaderSource(shader.fragmentShaderObject, 1, &fragment, NULL);
        glCompileShader(shader.fragmentShaderObject );
        glGetShaderiv( shader.fragmentShaderObject, GL_COMPILE_STATUS, &fragCompiled);
        printf("fragCompiled = %d\n", fragCompiled);
    }
    
    
    if (!vertCompiled || !fragCompiled)
        return 0;
    
    // Create a program object and attach the two compiled shaders
    
    shader.programObject = glCreateProgram();
    if (shader.vertexShaderObject)
    {
        glAttachShader( shader.programObject, shader.vertexShaderObject);
    }
    if (shader.fragmentShaderObject)
    {
        glAttachShader( shader.programObject, shader.fragmentShaderObject);
    }
    
    // Link the program object 
    
    glLinkProgram(shader.programObject);
    glGetProgramiv(shader.programObject, GL_LINK_STATUS, &linked);
    
    if (!linked)
    {
        printf("Shader program not linked successfully.\n");
        return 0;
    }
    
    return 1;
}
