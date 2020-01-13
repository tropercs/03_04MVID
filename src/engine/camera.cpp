#include "engine/camera.hpp"

#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(const glm::vec3& position, const glm::vec3& up, float yaw, float pitch)
 : _position(position), _worldUp(up), _yaw(yaw), _pitch(pitch), _fov(k_FOV) {
    updateCameraVectors();
}

Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch)
    : _position(glm::vec3(posX, posY, posZ)), _worldUp(glm::vec3(upX, upY, upZ)), _yaw(yaw), _pitch(pitch), _fov(k_FOV) {
    updateCameraVectors();
}

glm::mat4 Camera::getViewMatrix() const {
    return glm::lookAt(_position, _position + _front, _up);
}


glm::mat4 Camera::getViewMatrix(bool usemylookat) const {
    if (usemylookat) {
        return mylookAt(_position, _position + _front, _up);
    }
    return glm::lookAt(_position, _position + _front, _up);
}

float Camera::getFOV() const {
    return _fov;
}

glm::vec3 Camera::getPosition() const {
    return _position;
}

void Camera::updateCameraVectors() {
    glm::vec3 front;
    front.x = cos(glm::radians(_yaw)) * cos(glm::radians(_pitch));
    front.y = sin(glm::radians(_pitch));
    front.z = sin(glm::radians(_yaw)) * cos(glm::radians(_pitch));
    _front = glm::normalize(front);

    _right = glm::normalize(glm::cross(_front, _worldUp));
    _up = glm::normalize(glm::cross(_right, _front));
}

glm::mat4 Camera::mylookAt(glm::vec3 posCamara, glm::vec3 objetivo, glm::vec3 up) const {
    glm::mat4 matriz = glm::mat4(1.0f);
    glm::mat4 mCamara = glm::mat4(1.0f);
    mCamara[3][0] = -posCamara[0];
    mCamara[3][1] = -posCamara[1];
    mCamara[3][2] = -posCamara[2];
    glm::vec3 derecha, arriba, direccion;
    direccion = posCamara - objetivo;
    direccion = glm::normalize(direccion);
    derecha = glm::cross(up, direccion);
    derecha = glm::normalize(derecha);
    arriba = glm::cross(direccion, derecha);
    arriba = glm::normalize(arriba);
    matriz[0][0] = derecha[0];
    matriz[1][0] = derecha[1];
    matriz[2][0] = derecha[2];
    matriz[0][1] = arriba[0];
    matriz[1][1] = arriba[1];
    matriz[2][1] = arriba[2];
    matriz[0][2] = direccion[0];
    matriz[1][2] = direccion[1];
    matriz[2][2] = direccion[2];

    matriz = matriz * mCamara;
    return matriz;
}

void Camera::handleKeyboard(Movement direction, float dt) {
    const float velocity = k_Speed * dt;

    switch (direction) {
        case Movement::Forward: _position += _front * velocity; break;
        case Movement::Backward: _position -= _front * velocity; break;
        case Movement::Left: _position -= _right * velocity; break;
        case Movement::Right: _position += _right * velocity; break;
        default:;
    }
}

void Camera::handleMouseMovement(float xoffset, float yoffset, bool constrainPitch) {
    const float xoff = xoffset * k_Sensitivity;
    const float yoff = yoffset * k_Sensitivity;

    _yaw += xoff;
    _pitch += yoff;

    if (constrainPitch) {
        if (_pitch > 89.0f) _pitch = 89.0f;
        if (_pitch < -89.0f) _pitch = -89.0f;
    }

    updateCameraVectors();
}

void Camera::handleMouseScroll(float yoffset) {
    if (_fov >= 1.0f && _fov <= 45.0f) _fov -= yoffset;
    if (_fov <= 1.0f) _fov = 1.0f;
    if (_fov >= 45.0f) _fov = 45.0f;
}



