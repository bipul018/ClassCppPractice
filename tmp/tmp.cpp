#include <iostream>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h" /* http://nothings.org/stb/stb_image_write.h */

#define STB_TRUETYPE_IMPLEMENTATION 
#include "stb_truetype.h" /* http://nothings.org/stb/stb_truetype.h */



int main1() {
    /* load font file */
    long size;
    unsigned char* fontBuffer;

    FILE* fontFile = fopen("verdana.ttf", "rb");
    fseek(fontFile, 0, SEEK_END);
    size = ftell(fontFile); /* how long is the file ? */
    fseek(fontFile, 0, SEEK_SET); /* reset */

    fontBuffer = reinterpret_cast<unsigned char*>(malloc(size));

    fread(fontBuffer, size, 1, fontFile);
    fclose(fontFile);

    /* prepare font */
    stbtt_fontinfo info;
    if (!stbtt_InitFont(&info, fontBuffer, 0)) {
        printf("failed\n");
    }

    int b_w = 1028; /* bitmap width */
    int b_h = 1028; /* bitmap height */
    int l_h = 64; /* line height */

    /* create a bitmap for the phrase */
    unsigned char* bitmap = reinterpret_cast<unsigned char*>(calloc(b_w * b_h, sizeof(unsigned char)));


    struct Vec2 {
        float x;
        float y;

        float len() const {
            return sqrtf(x * x + y * y);
        }

        Vec2 operator -(Vec2 b) const {
            return Vec2{ x - b.x,y - b.y };
        }
         
        Vec2 operator +(Vec2 b) const {
            return Vec2{ x + b.x, y + b.y };
        }

        Vec2 unit() const {
            if (len() == 0.f)
                return Vec2{ 0.f,0.f };
            return Vec2{ x / len(),y / len() };
        }
        
        Vec2 normPerp() const {
            return Vec2{ unit().y, unit().x * -1.f };
        }
        Vec2 operator * (float f) const {
            return Vec2{ x * f,y * f };
        }
    };

    auto getpix = [&](Vec2 a, unsigned char *map = nullptr) {
        if (map == nullptr)
            map = bitmap;
        if (a.x >= 0.f && a.y >= 0.f && a.x < b_w && a.y < b_h) {

            int x = a.x;
            int y = a.y;

            float fx = a.x - x;
            float fy = a.y - y;

            int loc = y * b_w + x;

            return map[loc];
        }
        unsigned char c = 0;
        return c;

    };

    auto putpix = [&b_w, &b_h, &l_h, &bitmap](Vec2 a,unsigned char val, unsigned char* map = nullptr) {
        if (map == nullptr)
            map = bitmap;
        if (a.x >= 0.f && a.y >= 0.f && a.x < b_w && a.y < b_h) {

            int x = a.x;
            int y = a.y;

            float fx = a.x - x;
            float fy = a.y - y;

            int loc = y * b_w + x;

            map[loc] = val;
        }
    };

    auto makeLine = [&b_w, &b_h, &l_h, &bitmap,&putpix](Vec2 a,Vec2 b) {
        Vec2 diff = b - a;
        if (diff.len() == 0.f) {
            putpix(a, 255);
            return;
        }

        Vec2 step = diff.unit();

        Vec2 point = a;

        while ((point - a).len() <= diff.len() ) {
            putpix(point, 255);
            point = point + step;
        }

    };

    auto makeBezier = [&](Vec2 a, Vec2 b, Vec2 c) {
        Vec2 diff = c - a;
        if (diff.len() == 0.f) {
            putpix(a, 255);
            return;
        }

        putpix(a, 255);
        putpix(c, 255);

        Vec2 step = diff.unit()*0.1f;

        Vec2 point = a;

        Vec2 prevPoint = a;
        while ((point - a).len() <= diff.len()) {

            float t = (point - a).len() / diff.len();

            Vec2 nextPoint = a * (1.f - t) * (1.f - t) + b * 2.f * t * (1.f - t) + c * t * t;

            makeLine(prevPoint, nextPoint);
            prevPoint = nextPoint;

            point = point + step;
        }



    };



    /* calculate font scaling */
    float scale = stbtt_ScaleForPixelHeight(&info, l_h);

    const char* word = "the foxing $#!++!^& fox";

    int x = 0;

    int ascent, descent, lineGap;
    stbtt_GetFontVMetrics(&info, &ascent, &descent, &lineGap);

    ascent = roundf(ascent * scale);
    descent = roundf(descent * scale);

    int i;
    stbtt_vertex* pvertices;

    int num_vertices = stbtt_GetCodepointShape(&info, '@', &pvertices);

    Vec2 minV, maxV;

    minV.x = pvertices[0].x;
    minV.y = pvertices[0].y;
    maxV = minV;

    for (int i = 0; i < num_vertices; ++i) {

        std::cout << pvertices[i].x << "\t" << pvertices[i].y <<"\t" << pvertices[i].cx << "\t" << pvertices[i].cy << "\t" << pvertices[i].cx1
            << "\t" << pvertices[i].cy1 << "\t" << (int)pvertices[i].type << "\t" << (int)pvertices[i].padding << "\n";

        if (pvertices[i].x < minV.x)
            minV.x = pvertices[i].x;
        if (pvertices[i].y < minV.y)
            minV.y = pvertices[i].y;

        if (pvertices[i].x > maxV.x)
            maxV.x = pvertices[i].x;
        if (pvertices[i].y > maxV.y)
            maxV.y = pvertices[i].y;

        if (pvertices[i].type == 3) {

            if (pvertices[i].cx < minV.x)
                minV.x = pvertices[i].cx;
            if (pvertices[i].cy < minV.y)
                minV.y = pvertices[i].cy;

            if (pvertices[i].cx > maxV.x)
                maxV.x = pvertices[i].cx;
            if (pvertices[i].cy > maxV.y)
                maxV.y = pvertices[i].cy;

        }

    }

    Vec2 diffvec = maxV - minV;

    Vec2 mapvec = { b_w/3.f,b_h/3.f };
    Vec2 begvec = mapvec;
    mapvec.x = diffvec.x * b_h / (3.f * diffvec.y);

    
    auto convVert = [&](float x,float y) {
        Vec2 v = { x,y };
        v = v - minV;
        v = { v.x / diffvec.x, 1.f - v.y / diffvec.y };
        v = { v.x * mapvec.x,v.y * mapvec.y };
        v = v + begvec;
        return v;
    };
    

    for (int i = 0; i < num_vertices; ++i) {
        
        switch (pvertices[i].type) {
        case 1:
        {

            Vec2 p = convVert(pvertices[i].x, pvertices[i].y);
            makeLine(p, p);
        }


            break;
        case 2:
        {

            Vec2 p1 = convVert(pvertices[i - 1].x, pvertices[i - 1].y);
            Vec2 p2 = convVert(pvertices[i].x, pvertices[i].y);
            makeLine(p1, p2);

        }

            break;

        case 3:
        {

            Vec2 p1 = convVert(pvertices[i - 1].x, pvertices[i - 1].y);
            Vec2 p2 = convVert(pvertices[i].x, pvertices[i].y);
            Vec2 pc = convVert(pvertices[i].cx, pvertices[i].cy);
            //makeLine(p1, p1);
            //makeLine(p2, p2);
            //makeLine(pc, pc);
            makeBezier(p1, pc, p2);
        }
            break;
        }

    }


    /* create a bitmap for the phrase */
    unsigned char* xbitmap = reinterpret_cast<unsigned char*>(calloc(b_w * b_h, sizeof(unsigned char)));
    unsigned char* ybitmap = reinterpret_cast<unsigned char*>(calloc(b_w * b_h, sizeof(unsigned char)));

        memcpy(xbitmap, bitmap, b_w * b_h * sizeof(unsigned char));
        memcpy(ybitmap, bitmap, b_w * b_h * sizeof(unsigned char));

        for (float y = 0; y < b_h; y += 1.f) {
            bool fill = false;
            bool black = true;
            for (float x = 0; x < b_w; x += 1.f) {
                if (getpix(Vec2{ x,y }) > 100) {
                    if (black) {
                        fill = !fill;
                        black = false;
                    }
                }
                else {
                    if (!black) {
                        black = true;
                    }
                }
                if (fill)
                    putpix(Vec2{ x,y }, 255, ybitmap);
            }
        }


        for (float x = 0; x < b_w; x += 1.f) {
            bool fill = false;
            bool black = true;
            for (float y = 0; y < b_h; y += 1.f) {
                if (getpix(Vec2{ x,y }) > 100) {
                    if (black) {
                        fill = !fill;
                        black = false;
                    }
                }
                else {
                    if (!black) {
                        black = true;
                    }
                }
                if (fill)
                    putpix(Vec2{ x,y }, 255, xbitmap);
            }
        }

        for (float y = 0; y < b_h; y += 1.f) {
            for (float x = 0; x < b_w; x += 1.f) {

                if (getpix(Vec2{ x,y }, xbitmap) > 100 && getpix(Vec2{ x,y }, ybitmap) > 100)
                    putpix(Vec2{ x,y }, 255);

            }
        }
    

    free(xbitmap);
    free(ybitmap);
    Vec2 unitBox = { b_w / 10.f,b_h / 10.f };

    //memset(bitmap, 0, b_w* b_h * sizeof(unsigned char));

    Vec2 a, b, c;
    a = Vec2{ 10.f,10.f } + Vec2{b_w/2.f,b_h/2.f};
    b = Vec2{ 90.f,90.f } + Vec2{b_w/2.f,b_h/2.f};
    c = Vec2{ 10.f,50.f } + Vec2{b_w/2.f,b_h/2.f};
    
    //makeBezier(a, b, c);
    //
    //putpix(a, getpix(a) / 2);
    //putpix(c, getpix(c) / 2);




    for (int i = 0; i < 10; ++i) {
        
        for (int j = 0; j < 10; ++j) {
    
            Vec2 gcen = { b_w / 2.f,b_h / 2.f };
            Vec2 cen = { unitBox.x * i,unitBox.y * j };
            cen = cen + unitBox * 0.5f;
    
            Vec2 a, b, c;
            a = cen - unitBox * 0.45f;
            b = cen + unitBox * 0.45f;
            c = (gcen - cen).unit() * unitBox.len() * 0.75f + cen;
    
            //makeLine(c, c);
            //makeLine(b, b);
            //makeLine(c, c);
            //makeBezier(a, c, b); //
            //putpix(a, getpix(a) / 2);
            //putpix(b, getpix(b) / 2);


        }
    
    }


    stbtt_FreeShape(&info, pvertices);




    //for (i = 0; i < strlen(word); ++i) {
    //    /* how wide is this character */
    //    int ax;
    //    int lsb;
    //    stbtt_GetCodepointHMetrics(&info, word[i], &ax, &lsb);
    //    /* (Note that each Codepoint call has an alternative Glyph version which caches the work required to lookup the character word[i].) */

    //    /* get bounding box for character (may be offset to account for chars that dip above or below the line) */
    //    int c_x1, c_y1, c_x2, c_y2;
    //    stbtt_GetCodepointBitmapBox(&info, word[i], scale, scale, &c_x1, &c_y1, &c_x2, &c_y2);

    //    /* compute y (different characters have different heights) */
    //    int y = ascent + c_y1;

    //    /* render character (stride and offset is important here) */
    //    int byteOffset = x + roundf(lsb * scale) + (y * b_w);
    //    stbtt_MakeCodepointBitmap(&info, bitmap + byteOffset, c_x2 - c_x1, c_y2 - c_y1, b_w, scale, scale, word[i]);

    //    /* advance x */
    //    x += roundf(ax * scale);

    //    /* add kerning */
    //    int kern;
    //    kern = stbtt_GetCodepointKernAdvance(&info, word[i], word[i + 1]);
    //    x += roundf(kern * scale);
    //}

    /* save out a 1 channel image */
    stbi_write_png("out.png", b_w, b_h, 1, bitmap, b_w);

    /*
     Note that this example writes each character directly into the target image buffer.
     The "right thing" to do for fonts that have overlapping characters is
     MakeCodepointBitmap to a temporary buffer and then alpha blend that onto the target image.
     See the stb_truetype.h header for more info.
    */

    free(fontBuffer);
    free(bitmap);

    return 0;
}