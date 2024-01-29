void SDraw(const std::vector<Entity*>& entities) {
    for(int i=0;i<entities.size();i++) {
        window.clear();
        window.draw(entities[i]->cshape);
        window.display();
    }
};