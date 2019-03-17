uniform bool useObjRef;
uniform vec2 objRef;
uniform vec2 viewportSize;
uniform vec2 viewportOrigin;
attribute vec2 position;

void main() {
    vec2 pos = position;
    if(useObjRef) {
        pos += objRef;
    }
    pos -= viewportOrigin;
    gl_Position = vec4(pos * 2.0 / viewportSize, 0.0, 1.0);
}
