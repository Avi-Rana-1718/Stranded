#pragma once

class Vec2 {
    public:
    float x=0;
    float y=0;

    Vec2() {};
    Vec2(float xin, float yin);

    bool operator == (const Vec2& obj);
    bool operator != (const Vec2& obj);

    Vec2 operator + (const Vec2& obj);
    Vec2 operator - (const Vec2& obj);
    Vec2 operator * (const Vec2& obj);
    Vec2 operator / (const Vec2& obj);

    float distance(const Vec2& obj);   

};

// Vec2::Vec2() {
//     x=0;
//     y=0;
// }

Vec2::Vec2(float xin, float yin) {
    x=xin;
    y=yin;
}

bool Vec2::operator==(const Vec2& obj) {
    if((this->x==obj.x)&&(this->y==obj.y)) {
        return true;
    } else {
        return false;
    }
}

bool Vec2::operator!=(const Vec2& obj) {
    if((this->x!=obj.x)&&(this->y!=obj.y)) {
        return true;
    } else {
        return false;
    }
}

Vec2 Vec2::operator+(const Vec2& obj) {
    Vec2 temp;
    temp.x=this->x + obj.x;
    temp.y=this->y+ obj.y;
    return temp;
}

Vec2 Vec2::operator-(const Vec2& obj) {
    Vec2 temp;
    temp.x=this->x - obj.x;
    temp.y=this->y - obj.y;
    return temp;
}
Vec2 Vec2::operator*(const Vec2& obj) {
    Vec2 temp;
    temp.x=this->x*obj.x;
    temp.y=this->y*obj.y;
    return temp;
}

Vec2 Vec2::operator/(const Vec2& obj) {
    Vec2 temp;
    temp.x=this->x/obj.x;
    temp.y=this->y/obj.y;
    return temp;
}

float Vec2::distance(const Vec2& obj) {
    
    return (2.f);
}