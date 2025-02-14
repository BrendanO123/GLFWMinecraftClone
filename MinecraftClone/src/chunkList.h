#pragma once

#include <glm/glm.hpp>


struct chunkListNode
{
    glm::ivec2 pos;
    chunkListNode* next;

    chunkListNode(glm::ivec2 location, chunkListNode* pointer = nullptr): 
    pos(location), next(pointer){};
};

struct chunkList{
    chunkListNode* first;
    chunkListNode* last;
    int count;

    chunkList(chunkListNode* next = nullptr) : first(next), last(next), count(next == nullptr ? 0 : 1){}
    ~chunkList(){
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
        last->next = new chunkListNode(glm::ivec2(x, y));
        last = last->next;
        count++;
    }

    void pushFront(int x, int y){
        first = new chunkListNode(glm::ivec2(x, y), first);
        count++;
    }

    bool empty(){return count == 0;}

    glm::ivec2 pop(){return popFront();}
    glm::ivec2 popFront(){
        chunkListNode* temp = first;
        glm :: ivec2 returnValue = first->pos;
        first = first->next;
        delete temp;
        return returnValue;
    }

    glm :: ivec2 getFirst(){return first->pos;}
    glm :: ivec2 getLast(){return last->pos;}
};