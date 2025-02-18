#pragma once

#include <glm/glm.hpp>


struct chunkListNode
{
    int x, y;
    chunkListNode* next;

    chunkListNode(int X, int Y, chunkListNode* pointer = nullptr): 
    x(X), y(Y), next(pointer){};
};

struct chunkList{
    chunkListNode* first;
    chunkListNode* last;
    int count;

    chunkList(chunkListNode* next = nullptr) : first(next), last(next), count(next == nullptr ? 0 : 1){}
    ~chunkList(){
        count = 0;
        chunkListNode* iterate = first;
        chunkListNode* next;
        while(iterate != nullptr){
            next = iterate->next;
            delete iterate;
            iterate = next;
        }
    }

    void push(int x, int y){pushBack(x,y);}
    void pushBack(int x, int y){
        if(last == nullptr && first == nullptr){
            last = first = new chunkListNode(x, y);
            count = 1;
        }
        else{
            last->next = new chunkListNode(x, y);
            last = last->next;
            count++;
        }
    }

    void pushFront(int x, int y){
        first = new chunkListNode(x, y, first);
        count++;
    }

    bool empty(){return count <= 0;}

    glm::ivec2 pop(){return popFront();}
    glm::ivec2 popFront(){
        chunkListNode* temp = first;
        glm :: ivec2 returnValue = glm :: ivec2(first->x, first->y);
        first = first->next;
        count--;
        delete temp;
        return returnValue;
    }

    glm :: ivec2 getFirst(){return glm :: ivec2(first->x, first->y);}
    glm :: ivec2 getLast(){return glm :: ivec2(last->x, last->y);}
};