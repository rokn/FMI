#include "PostsDAOMemory.h"

PostsDAOMemory::PostsDAOMemory()
: currentId(0) {

}

PostsDAOMemory::~PostsDAOMemory() {
    for (int i = 0; i < posts.getSize(); ++i) {
        delete posts[i];
    }
}

bool PostsDAOMemory::addPost(Post *post) {
    post->setId(getNewId());
    posts.addBack(post);
    return true; // TODO: do we need bool?
}

Post *PostsDAOMemory::getPost(unsigned id) {
    for (int i = 0; i < posts.getSize(); ++i) {
        if(posts[i]->getId() == id) {
            return posts[i];
        }
    }

    return nullptr;
}

Post *PostsDAOMemory::getPostsBy(const char *nickname) {
    return nullptr;
}

unsigned int PostsDAOMemory::getPostCount(const char *nickname) {
    unsigned counter = 0;
    for (int i = 0; i < posts.getSize(); ++i) {
        if(posts[i]->() == id) {
            return posts[i];
        }
    }

    return counter;
}

unsigned int PostsDAOMemory::getNewId() {
    return currentId++;
}
