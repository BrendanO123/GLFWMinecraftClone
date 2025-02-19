#include "BlockHighlighter.h"

#include <glm/gtc/type_ptr.hpp>

BlockHighlighter :: ~BlockHighlighter(){
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteVertexArrays(1, &VAO);
}
BlockHighlighter :: BlockHighlighter(Shader shader){

    int vOffset = 0;
    verticies.emplace_back(                   0, 0,   0, ColorPositionX, ColorPositionY, 4);
    verticies.emplace_back((scale), 0,   0, ColorPositionX+1, ColorPositionY, 4);
    verticies.emplace_back(                   0, scale, 0, ColorPositionX, ColorPositionY+1, 4);
    verticies.emplace_back((scale), scale, 0, ColorPositionX+1, ColorPositionY+1, 4);

    indicies.push_back(vOffset); indicies.push_back(vOffset+2); indicies.push_back(vOffset+1);
    indicies.push_back(vOffset+3); indicies.push_back(vOffset+1); indicies.push_back(vOffset+2);
    vOffset+=4;


    verticies.emplace_back((scale), 0,   0,                    ColorPositionX, ColorPositionY, 4);
    verticies.emplace_back((scale), 0,   (-scale), ColorPositionX+1, ColorPositionY, 4);
    verticies.emplace_back((scale), scale, 0,                    ColorPositionX, ColorPositionY+1, 4);
    verticies.emplace_back((scale), scale, (-scale), ColorPositionX+1, ColorPositionY+1, 4);

    indicies.push_back(vOffset); indicies.push_back(vOffset+2); indicies.push_back(vOffset+1);
    indicies.push_back(vOffset+3); indicies.push_back(vOffset+1); indicies.push_back(vOffset+2);
    vOffset+=4;


    verticies.emplace_back((scale), 0,   (-scale), ColorPositionX, ColorPositionY, 4);
    verticies.emplace_back(                   0, 0,   (-scale), ColorPositionX+1, ColorPositionY, 4);
    verticies.emplace_back((scale), scale, (-scale), ColorPositionX, ColorPositionY+1, 4);
    verticies.emplace_back(                   0, scale, (-scale), ColorPositionX+1, ColorPositionY+1, 4);

    indicies.push_back(vOffset); indicies.push_back(vOffset+2); indicies.push_back(vOffset+1);
    indicies.push_back(vOffset+3); indicies.push_back(vOffset+1); indicies.push_back(vOffset+2);
    vOffset+=4;

    verticies.emplace_back(                   0, 0,   (-scale), ColorPositionX, ColorPositionY, 4);
    verticies.emplace_back(                   0, 0,   0,                    ColorPositionX+1, ColorPositionY, 4);
    verticies.emplace_back(                   0, scale, (-scale), ColorPositionX, ColorPositionY+1, 4);
    verticies.emplace_back(                   0, scale, 0,                    ColorPositionX+1, ColorPositionY+1, 4);

    indicies.push_back(vOffset); indicies.push_back(vOffset+2); indicies.push_back(vOffset+1);
    indicies.push_back(vOffset+3); indicies.push_back(vOffset+1); indicies.push_back(vOffset+2);
    vOffset+=4;

    verticies.emplace_back(                   0, scale, 0,                   ColorPositionX,ColorPositionY, 4);
    verticies.emplace_back((scale), scale, 0,                   ColorPositionX+1,ColorPositionY, 4);
    verticies.emplace_back(                   0, scale, (-scale),ColorPositionX,ColorPositionY+1, 4);
    verticies.emplace_back((scale), scale, (-scale),ColorPositionX+1,ColorPositionY+1, 4);

    indicies.push_back(vOffset); indicies.push_back(vOffset+2); indicies.push_back(vOffset+1);
    indicies.push_back(vOffset+3); indicies.push_back(vOffset+1); indicies.push_back(vOffset+2);
    vOffset+=4;


    verticies.emplace_back(                   0, 0,   (-scale), ColorPositionX, ColorPositionY, 4);
    verticies.emplace_back((scale), 0,   (-scale), ColorPositionX+1, ColorPositionY, 4);
    verticies.emplace_back(                   0, 0,   0,                      ColorPositionX, ColorPositionY+1, 4);
    verticies.emplace_back((scale), 0,   0,                      ColorPositionX+1, ColorPositionY+1, 4);

    indicies.push_back(vOffset); indicies.push_back(vOffset+2); indicies.push_back(vOffset+1);
    indicies.push_back(vOffset+3); indicies.push_back(vOffset+1); indicies.push_back(vOffset+2);
    
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, verticies.size() * sizeof(FVertex), verticies.data(), GL_STATIC_DRAW);

    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicies.size() * sizeof(GLuint), indicies.data(), GL_STATIC_DRAW);

    GLuint posLoc = glGetAttribLocation(shader.program, "vPos");
    GLuint heightLoc = glGetAttribLocation(shader.program, "height");
    GLuint vtexPos_location = glGetAttribLocation(shader.program, "vtexPos");
    GLuint vNormalLoc = glGetAttribLocation(shader.program, "normal");
    modelMatLoc = glGetUniformLocation(shader.program, "modelPos");


    glEnableVertexAttribArray(vtexPos_location);
    glVertexAttribPointer(vtexPos_location, 2, GL_UNSIGNED_BYTE, GL_FALSE, sizeof(FVertex), (void*) (offsetof(FVertex, texPosX)));

    glEnableVertexAttribArray(posLoc);
    glVertexAttribPointer(posLoc, 2, GL_FLOAT, GL_FALSE, sizeof(FVertex), (void*) (offsetof(FVertex, posX)));

    glEnableVertexAttribArray(heightLoc);
    glVertexAttribPointer(heightLoc, 1, GL_FLOAT, GL_FALSE, sizeof(FVertex), (void*) (offsetof(FVertex, posY)));

    glEnableVertexAttribArray(vNormalLoc);
    glVertexAttribPointer(vNormalLoc, 1, GL_UNSIGNED_BYTE, GL_FALSE, sizeof(FVertex), (void*) (offsetof(FVertex, NormalSelector)));
}

void BlockHighlighter :: highlight(glm :: ivec3 position){
    glUniform3iv(modelMatLoc, 1, glm::value_ptr(position));

    glDisable(GL_CULL_FACE);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indicies.size(), GL_UNSIGNED_INT, 0);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glEnable(GL_CULL_FACE);
}