uint32_t rnd(){
    static uint32_t x = 123456789, y = 362436069, z = 521288629, w = 0;
    uint32_t t = x ^ (x << 11);
    x = y;
    y = z;
    z = w;
    w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));
    return w;
}

double rnd_double(){
    return 1.0 * rnd() / numeric_limits<uint32_t>::max();
}

