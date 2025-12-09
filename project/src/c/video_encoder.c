#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include <getopt.h>

#include <cairo.h>
#include <cairo-ft.h>
#include <cairo-pdf.h>

#include <libavcodec/avcodec.h>
#include <libavutil/avutil.h>
#include <libavformat/avformat.h>
#include <libavutil/opt.h>

/* Helper function to encode a frame and write to format context */
static int encode_frame_to_container(AVCodecContext *enc_ctx, AVFrame *frame, 
                                      AVFormatContext *fmt_ctx, AVStream *stream) {
    AVPacket *pkt = av_packet_alloc();
    int ret;
    int bytes_written = 0;

    if (!pkt) {
        fprintf(stderr, "Could not allocate packet\n");
        return -1;
    }

    ret = avcodec_send_frame(enc_ctx, frame);
    if (ret < 0 && ret != AVERROR_EOF && ret != AVERROR(EAGAIN)) {
        fprintf(stderr, "Error sending frame for encoding: %d\n", ret);
        av_packet_free(&pkt);
        return -1;
    }

    while (ret >= 0) {
        ret = avcodec_receive_packet(enc_ctx, pkt);
        if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF) {
            break;
        } else if (ret < 0) {
            fprintf(stderr, "Error during encoding: %d\n", ret);
            av_packet_free(&pkt);
            return -1;
        }
        
        /* Rescale packet timestamp */
        av_packet_rescale_ts(pkt, enc_ctx->time_base, stream->time_base);
        pkt->stream_index = stream->index;
        
        /* Write packet to container */
        ret = av_interleaved_write_frame(fmt_ctx, pkt);
        if (ret < 0) {
            fprintf(stderr, "Error writing packet: %d\n", ret);
            av_packet_free(&pkt);
            return -1;
        }
        bytes_written += pkt->size;
        av_packet_unref(pkt);
    }

    av_packet_free(&pkt);
    return bytes_written;
}

#include "EVGLinkedList.h"
#include "UIStructure.h"
#include "UINativeText.h"
#include "UIXMLParser.h"
#include "UICalculateLayout.h"

// 
#include <libxml/parser.h>

#include "duktape.h"

// http://www.html5rocks.com/en/tutorials/canvas/texteffects/


// Example of pure JS XML parser
// http://ejohn.org/files/htmlparser.js

void renderXMLToSurface(char *xmlStr);

char* concat(char *s1, char *s2)
{
  int length_of = strlen(s1)+strlen(s2);
  char *result = malloc(length_of+1);//+1 for the zero-terminator
  //in real code you would check for errors in malloc here
  strcpy(result, s1);
  strcat(result, s2);
  result[length_of] = '\0'; 
  return result;
}

/* strdup is provided by _GNU_SOURCE, custom implementation removed */

static void push_file_as_string(duk_context *ctx, const char *filename) {
    FILE *f;
    size_t len;
    char buf[16384];

    f = fopen(filename, "rb");
    if (f) {
        len = fread((void *) buf, 1, sizeof(buf), f);
        fclose(f);
        duk_push_lstring(ctx, (const char *) buf, (duk_size_t) len);
    } else {
        duk_push_undefined(ctx);
    }
}



// embedding the ductape at the server side
/*
#include "duktape.h"
 
int adder(duk_context *ctx) {
 int i;
 int n = duk_get_top(ctx);
 double res = 0.0;

 for (i = 0; i < n; i++) {
    res += duk_to_number(ctx, i);
 }

 duk_push_number(ctx, res);
 return 1;
}

int main(int argc, char *argv[]) {

}
*/


static LinkedList *__alphaList = NULL;
static UIFloatType *currentAlphaValue = NULL;

double getGlobalAlpha( double usingValue  ) {
    
    if(currentAlphaValue != NULL) {
        
        double res = usingValue * currentAlphaValue->f_value;
        
        return res;
    }
    return usingValue;
    
}

double pushGlobalAlpha( double value ) {
    
    value = value * getGlobalAlpha( 1.0 );
    
    UIFloatType *newFloatValue = UIFloatType_New();
    newFloatValue->f_value = value;
    
    if(!__alphaList) __alphaList = createList();
    
    LinkedListNode *saveItem = ListNode_Create(strdup("float"), newFloatValue);
    List_push( __alphaList, saveItem );
    
    currentAlphaValue = newFloatValue;
    
    setTextAlpha( value );
    
}

void popGlobalAlpha() {
    
    if(!__alphaList) __alphaList = createList();
    
    LinkedListNode *lastAlphaValue = List_pop( __alphaList );
    
    if( lastAlphaValue != NULL ) {
        
        UIFloatType *last = (UIFloatType*) lastAlphaValue->data;
        if( __alphaList->tail ) {
            LinkedListNode *lastItem = __alphaList->tail;
            
            currentAlphaValue = (UIFloatType*)lastItem->data;
        } else {
            currentAlphaValue = NULL;
        }
        if(currentAlphaValue) {
            // UIFloatType *curr = (UIFloatType*) currentAlphaValue->data;
            setTextAlpha( currentAlphaValue->f_value );
        }
    } else {
        // printf("*** popGlobalAlpha while nothing to pop :/  \n");
        currentAlphaValue = NULL;
    }
}



int video_buf_width  = 800;
int video_buf_height = 600;

cairo_surface_t *surface = NULL;
cairo_t *cr = NULL;


// creating the shadow
// http://taschenorakel.de/gitweb/?p=playground;a=blob;f=blur-effect/blur-effect.c



/*
cairo_font_face_t *crFace;
cairo_matrix_t identityMatrix;
cairo_matrix_init_identity(&identityMatrix);
cairo_scaled_font_t *sfPtr;
*/



// #include <libswscale/swscale.h>

// https://raw.githubusercontent.com/pontago/objc-FFmpegAudioTest/master/FFmpeg/doc/examples/encoding-example.c
// https://blinkingblip.wordpress.com/2011/10/08/decoding-and-playing-an-audio-stream-using-libavcodec-libavformat-and-libao/
// https://rosettacode.org/wiki/Example:Hough_transform/C
// https://ffmpeg.org/doxygen/trunk/muxing_8c-source.html
// http://dranger.com/ffmpeg/tutorial01.html
// https://ffmpeg.org/doxygen/trunk/encoding-example_8c-source.html


#define INBUF_SIZE 4096
#define AUDIO_INBUF_SIZE 20480
#define AUDIO_REFILL_THRESH 4096

// Parsing linear gradient...
// [ <angle> | to <side-or-corner> ,]? <color-stop> [, <color-stop>]+ )




static void update_cairo_surface(char *txt) {
    
    if(surface != NULL) {
        cairo_destroy(cr);
        cairo_surface_destroy(surface);
    }
    
    surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, 352, 288);
    cr = cairo_create(surface);
    
    cairo_set_source_rgb(cr, 255, 255, 255);
    
    FT_Face ftFace;
    FT_Error ftError;
    FT_Library library;
    
    
    cairo_font_face_t *crFace;
    
    cairo_matrix_t identityMatrix;
    cairo_matrix_init_identity(&identityMatrix);
    cairo_scaled_font_t *sfPtr;
    
    ftError = FT_Init_FreeType(&library);
    if(ftError) {
        printf("Error initializing the Freetype");
        return;
    }
    
    int faceIdx = 0;
    
    const char *filePath = "/var/www/static/Creepster/Creepster-Regular.ttf";
    // const char *filePath = "/var/www/static/Forum/Forum-Regular.ttf";
    ftError = FT_New_Face(library, filePath, faceIdx, &ftFace);
    if(ftError)  {
        printf("Error FT_New_Face");
        return;
    }
    
    crFace = cairo_ft_font_face_create_for_ft_face(ftFace, 0);
    cairo_set_font_face( cr, crFace );
    cairo_set_font_size(cr, 40.0);
    
    cairo_move_to(cr, 10.0, 50.0);
    cairo_show_text(cr, txt);
    
    
}

duk_context *ctx = NULL;
static void init_duktape(const char *jsFile) {
    ctx = duk_create_heap_default();
    if (!ctx) {
        printf("Failed to create a Duktape heap.\n");
        exit(1);
    }
    
  push_file_as_string(ctx, jsFile);
  if (duk_peval(ctx) != 0) {
    printf("Error: %s\n", duk_safe_to_string(ctx, -1));
    // goto finished;
    exit(1);
  }
  duk_pop(ctx);  /* ignore result */
    /*
finished:
    duk_destroy_heap(ctx);
    exit(1);
     */
}

static void call_duktape_str(int frameNumber) {
    
    char *resVal;
    char idx;
    int ch;
    char *line = "OK";
    
    /* Debug: print frame number being passed for first 5 frames and every 100 */
    if (frameNumber < 5 || frameNumber % 100 == 0) {
        printf("DEBUG: Calling processLine with frameNumber=%d\n", frameNumber);
    }
    
    duk_push_global_object(ctx);
    duk_get_prop_string(ctx, -1 /*index*/, "processLine");
    duk_push_number(ctx, frameNumber);
    
    if (duk_pcall(ctx, 1 /*nargs*/) != 0) {
        printf("Error calling processLine: %s\n", duk_safe_to_string(ctx, -1));
    } else {
        resVal = duk_safe_to_string(ctx, -1);
        // Debug: print full XML for first frame, snippet for others
        if (frameNumber == 0) {
            printf("DEBUG: Frame 0 FULL XML:\n%s\n", resVal);
        } else if (frameNumber < 5 || frameNumber % 100 == 0) {
            printf("DEBUG: Frame %d XML (first 200 chars): %.200s...\n", frameNumber, resVal);
        }
        if (resVal && strlen(resVal) > 0) {
            renderXMLToSurface(resVal);
        } else {
            printf("WARNING: processLine returned empty string for frame %d\n", frameNumber);
        }
    }
    duk_pop(ctx);  /* pop result/error */
    duk_pop(ctx);  /* pop global object */
    
}

// cairo_pdf_surface_create

static void create_cairo_pdf() {
    
    if(surface != NULL) {
        cairo_destroy(cr);
        cairo_surface_destroy(surface);
    }
    
    surface = cairo_pdf_surface_create("/var/www/static/cpp/cairo_test.pdf", 600, 800);
    cr = cairo_create(surface);
    
    cairo_set_source_rgb(cr, 120, 0, 0);
    
    FT_Face ftFace;
    FT_Error ftError;
    FT_Library library;
    
    cairo_font_face_t *crFace;
    cairo_matrix_t identityMatrix;
    cairo_matrix_init_identity(&identityMatrix);
    cairo_scaled_font_t *sfPtr;
    
    ftError = FT_Init_FreeType(&library);
    if(ftError) {
        printf("Error initializing the Freetype");
        return;
    }
    
    int faceIdx = 0;
    
    const char *filePath = "/var/www/static/Creepster/Creepster-Regular.ttf";
    // const char *filePath = "/var/www/static/Forum/Forum-Regular.ttf";
    ftError = FT_New_Face(library, filePath, faceIdx, &ftFace);
    if(ftError)  {
        printf("Error FT_New_Face");
        return;
    }
    
    crFace = cairo_ft_font_face_create_for_ft_face(ftFace, 0);
    cairo_set_font_face( cr, crFace );
    cairo_set_font_size(cr, 40.0);
    
    cairo_move_to(cr, 10.0, 50.0);
    cairo_show_text(cr, "Hello video!");
    
    cairo_show_page(cr);
    
    cairo_surface_flush(surface);
 
    cairo_destroy(cr);
    cairo_surface_destroy(surface);
    
}

static void create_cairo() {

    if(surface != NULL) {
        cairo_destroy(cr);
        cairo_surface_destroy(surface);
    }
    
        /* Use the video dimensions for the Cairo surface */
        surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, video_buf_width, video_buf_height);
        cr = cairo_create(surface);
        
        /* Initialize with white background */
        cairo_set_source_rgb(cr, 1.0, 1.0, 1.0);
        cairo_paint(cr);
        
        FT_Face ftFace;
        FT_Error ftError;
        FT_Library library;
        
        cairo_font_face_t *crFace;
        cairo_matrix_t identityMatrix;
        cairo_matrix_init_identity(&identityMatrix);
        cairo_scaled_font_t *sfPtr;
        
        ftError = FT_Init_FreeType(&library);
        if(ftError) {
            printf("Error initializing the Freetype");
            return;
        }
        
        int faceIdx = 0;
        
        const char *filePath = "/var/www/static/Creepster/Creepster-Regular.ttf";
        // const char *filePath = "/var/www/static/Forum/Forum-Regular.ttf";
        ftError = FT_New_Face(library, filePath, faceIdx, &ftFace);
        if(ftError)  {
            printf("Error FT_New_Face");
            return;
        }
        
        crFace = cairo_ft_font_face_create_for_ft_face(ftFace, 0);
        cairo_set_font_face( cr, crFace );
        cairo_set_font_size(cr, 40.0);
        
        cairo_move_to(cr, 10.0, 50.0);
        cairo_show_text(cr, "Hello video!");
        

}

unsigned char clamp(int n){
    int a = 255;
    a -= n;
    a >>= 31;
    a |= n;
    n >>= 31;
    n = ~n;
    n &= a;
    return n;
}

static void video_encode_example(const char *filename)
{
    const AVCodec *codec;
    AVCodecContext *codec_ctx = NULL;
    AVFormatContext *fmt_ctx = NULL;
    AVStream *video_stream = NULL;
    AVFrame *picture = NULL;
    
    int i, ret, size, x, y;
    uint8_t *picture_buf;
    
    printf("Video encoding to %s\n", filename);
    
    /* Allocate output format context - auto-detect from filename */
    ret = avformat_alloc_output_context2(&fmt_ctx, NULL, NULL, filename);
    if (ret < 0 || !fmt_ctx) {
        printf("Could not create output context\n");
        return;
    }
    printf("Output format: %s\n", fmt_ctx->oformat->name);
    
    /* Find encoder - use H.264 for MP4, MPEG1 for MPG */
    if (strcmp(fmt_ctx->oformat->name, "mp4") == 0 || 
        strcmp(fmt_ctx->oformat->name, "mov") == 0) {
        codec = avcodec_find_encoder(AV_CODEC_ID_MPEG4);  /* More compatible than H.264 */
    } else {
        codec = avcodec_find_encoder(AV_CODEC_ID_MPEG1VIDEO);
    }
    
    if (!codec) {
        printf("Codec not found\n");
        avformat_free_context(fmt_ctx);
        return;
    }
    printf("Codec: %s\n", codec->name);
    
    /* Create new video stream */
    video_stream = avformat_new_stream(fmt_ctx, NULL);
    if (!video_stream) {
        printf("Could not create video stream\n");
        avformat_free_context(fmt_ctx);
        return;
    }
    
    /* Allocate codec context */
    codec_ctx = avcodec_alloc_context3(codec);
    if (!codec_ctx) {
        printf("Could not allocate codec context\n");
        avformat_free_context(fmt_ctx);
        return;
    }
    
    /* Set codec parameters */
    codec_ctx->bit_rate = 800000;
    codec_ctx->width = video_buf_width;
    codec_ctx->height = video_buf_height;
    codec_ctx->time_base = (AVRational){1, 25};
    codec_ctx->framerate = (AVRational){25, 1};
    codec_ctx->gop_size = 10;
    codec_ctx->max_b_frames = 1;
    codec_ctx->pix_fmt = AV_PIX_FMT_YUV420P;
    
    /* Some formats want stream headers to be separate */
    if (fmt_ctx->oformat->flags & AVFMT_GLOBALHEADER)
        codec_ctx->flags |= AV_CODEC_FLAG_GLOBAL_HEADER;
    
    /* Open codec */
    ret = avcodec_open2(codec_ctx, codec, NULL);
    if (ret < 0) {
        printf("Error opening codec: %d\n", ret);
        avcodec_free_context(&codec_ctx);
        avformat_free_context(fmt_ctx);
        return;
    }
    
    /* Copy codec parameters to stream */
    ret = avcodec_parameters_from_context(video_stream->codecpar, codec_ctx);
    if (ret < 0) {
        printf("Could not copy codec parameters\n");
        avcodec_free_context(&codec_ctx);
        avformat_free_context(fmt_ctx);
        return;
    }
    video_stream->time_base = codec_ctx->time_base;
    
    /* Open output file */
    if (!(fmt_ctx->oformat->flags & AVFMT_NOFILE)) {
        ret = avio_open(&fmt_ctx->pb, filename, AVIO_FLAG_WRITE);
        if (ret < 0) {
            printf("Could not open output file '%s'\n", filename);
            avcodec_free_context(&codec_ctx);
            avformat_free_context(fmt_ctx);
            return;
        }
    }
    
    /* Write file header */
    ret = avformat_write_header(fmt_ctx, NULL);
    if (ret < 0) {
        printf("Error writing header: %d\n", ret);
        avcodec_free_context(&codec_ctx);
        avformat_free_context(fmt_ctx);
        return;
    }
    
    /* Allocate frame */
    picture = av_frame_alloc();
    if (!picture) {
        printf("Could not allocate frame\n");
        avcodec_free_context(&codec_ctx);
        avformat_free_context(fmt_ctx);
        return;
    }
    
    picture->format = codec_ctx->pix_fmt;
    picture->width = codec_ctx->width;
    picture->height = codec_ctx->height;
    
    /* Allocate frame buffer */
    size = codec_ctx->width * codec_ctx->height;
    picture_buf = malloc((size * 3) / 2);
    
    picture->data[0] = picture_buf;
    picture->data[1] = picture->data[0] + size;
    picture->data[2] = picture->data[1] + size / 4;
    picture->linesize[0] = codec_ctx->width;
    picture->linesize[1] = codec_ctx->width / 2;
    picture->linesize[2] = codec_ctx->width / 2;
    
    cairo_surface_flush(surface);
    char *imgData = cairo_image_surface_get_data(surface);
    
    int frameNumber = 0;
    int total_frames = 500;  /* 20 seconds at 25fps */
    int total_bytes = 0;
    int out_size;

    printf("Starting to encode %d frames at %dx%d\n", total_frames, codec_ctx->width, codec_ctx->height);
    
    /* Encode frames */
    for(i = 0; i < total_frames; i++) {
        fflush(stdout);
        
        /* Update surface with new frame from JavaScript */
        call_duktape_str(frameNumber++);
        
        /* Get the updated surface data - surface may have been recreated */
        cairo_surface_flush(surface);
        imgData = cairo_image_surface_get_data(surface);
        
        /* Debug: check surface status */
        if (i == 0) {
            int surf_width = cairo_image_surface_get_width(surface);
            int surf_height = cairo_image_surface_get_height(surface);
            int stride = cairo_image_surface_get_stride(surface);
            printf("Surface: %dx%d, stride=%d, data=%p\n", surf_width, surf_height, stride, imgData);
        }
        
        if (!imgData) {
            fprintf(stderr, "Error: Could not get surface data for frame %d\n", i);
            continue;
        }
        
        /* Get the actual stride from Cairo */
        int stride = cairo_image_surface_get_stride(surface);
        
        /* Convert BGRA to YUV420P */
        for(y = 0; y < codec_ctx->height; y++) {
            for(x = 0; x < codec_ctx->width; x++) {
                /* Use stride instead of width*4 for correct row access */
                uint8_t b = imgData[y * stride + x*4 + 0];
                uint8_t g = imgData[y * stride + x*4 + 1];
                uint8_t r = imgData[y * stride + x*4 + 2];
                
                uint8_t YY = ((66*r + 129*g + 25*b) >> 8) + 16;
                picture->data[0][y * picture->linesize[0] + x] = YY;
                
                if ((y % 2 == 0) && (x % 2 == 0)) {
                    int yy = y / 2;
                    int xx = x / 2;
                    uint8_t UU = ((-38*r + -74*g + 112*b) >> 8) + 128;
                    uint8_t VV = ((112*r + -94*g + -18*b) >> 8) + 128;
                    picture->data[1][yy * picture->linesize[1] + xx] = UU;
                    picture->data[2][yy * picture->linesize[2] + xx] = VV;
                }
            }
        }
        
        /* Encode the frame */
        picture->pts = i;
        out_size = encode_frame_to_container(codec_ctx, picture, fmt_ctx, video_stream);
        total_bytes += (out_size > 0) ? out_size : 0;
        
        if (i % 25 == 0) {
            printf("encoding frame %3d (size=%5d, total=%d bytes)\n", i, out_size, total_bytes);
        }
    }
    
    /* Flush encoder */
    printf("Flushing encoder...\n");
    out_size = encode_frame_to_container(codec_ctx, NULL, fmt_ctx, video_stream);
    while(out_size > 0) {
        total_bytes += out_size;
        printf("flushing (size=%5d)\n", out_size);
        out_size = encode_frame_to_container(codec_ctx, NULL, fmt_ctx, video_stream);
    }
    
    /* Write file trailer */
    av_write_trailer(fmt_ctx);
    
    printf("Total video data written: %d bytes\n", total_bytes);
    
    /* Cleanup */
    free(picture_buf);
    av_frame_free(&picture);
    avcodec_free_context(&codec_ctx);
    if (!(fmt_ctx->oformat->flags & AVFMT_NOFILE))
        avio_closep(&fmt_ctx->pb);
    avformat_free_context(fmt_ctx);
    
    printf("Video encoding complete!\n");
    return;
   
   
   
	
/*	
     
     uint8_t inbuf[INBUF_SIZE + FF_INPUT_BUFFER_PADDING_SIZE];
     char buf[1024];
     AVPacket avpkt;
   
     av_init_packet(&avpkt);
*/     
}

static void start_video_encoding(const char *jsFile, const char *outputFile) {
    
    /* av_register_all() is deprecated and no longer needed in modern FFmpeg */
    create_cairo();
    
    init_duktape(jsFile);
    
    video_encode_example(outputFile);
    
    if(cr) {
        cairo_destroy(cr);
        cairo_surface_destroy(surface);
    }
    
    if(ctx) {
        duk_destroy_heap(ctx);
        ctx = NULL;
    }
    
    // stream must be built using:
    // ffmpeg -i video.mp4stream video.mp4
    
    printf("Video encoding completed: %s\n", outputFile);
}


// 1. parse XML document
// 2. make the layout in C language
// 3. render output of the structure into some surface
//
// --> effect and animations could be externalized



static void create_rounded_rect(cairo_t *cr,
                                double sx,
                                double sy,
                                double ex,
                                double ey,
                                double r) {
    double r2d = M_PI / 180.0;
    
    if( ( ex - sx ) - ( 2 * r ) < 0 ) { r = ( ( ex - sx ) / 2 ); } //ensure that the radius isn't too large for x
    if( ( ey - sy ) - ( 2 * r ) < 0 ) { r = ( ( ey - sy ) / 2 ); } //ensure that the radius isn't too large for y
    
    cairo_new_path(cr);
    
    cairo_move_to( cr, sx,   sy );
    cairo_line_to( cr, ex-r, sy );
    cairo_arc( cr, ex-r,sy+r,r,r2d*270.0,r2d*360.0 );
    
    cairo_line_to( cr, ex, ey-r);
    cairo_arc( cr, ex-r,ey-r,r,r2d*0,r2d*90 );
    
    cairo_line_to( cr,sx+r,ey);
    cairo_arc (cr, sx+r,ey-r,r,r2d*90,r2d*180);
    cairo_line_to( cr,sx,sy+r);
    cairo_arc( cr, sx+r,sy+r,r,r2d*180,r2d*270);
    
    
}

// Some support linked lists for the images
/*
 
typedef struct LinkedListNode {
    char *name;
    void *data;
    struct LinkedListNode *prev;
} LinkedListNode;

typedef struct LinkedList {
    struct LinkedListNode * tail;
} LinkedList;


*/

LinkedList *imageList = NULL;


int font_loaded = 0;

FT_Face ftFace;
FT_Error ftError;
FT_Library library;
cairo_scaled_font_t *sfPtr;
cairo_font_face_t *crFace = NULL;


static char* stradd(const char* a, const char* b){
    size_t len = strlen(a) + strlen(b);
    char *ret = (char*)malloc(len * sizeof(char) + 1);
    *ret = '\0';
    return strcat(strcat(ret, a) ,b);
}

static void render_text( cairo_t *cr, UIStructure *ui ) {
    
    /*
    if(crFace == NULL) {
      cairo_matrix_t identityMatrix;
      cairo_matrix_init_identity(&identityMatrix);
    
        
    
      ftError = FT_Init_FreeType(&library);
      if(ftError) {
        printf("Error initializing the Freetype");
        return;
      }
    
      int faceIdx = 0;
    
      // const char *filePath = "/var/www/static/Creepster/Creepster-Regular.ttf";
      const char *filePath = "/var/www/static/Forum/Forum-Regular.ttf";
      ftError = FT_New_Face(library, filePath, faceIdx, &ftFace);
      if(ftError)  {
        printf("Error FT_New_Face");
        return;
      }
    
       crFace = cairo_ft_font_face_create_for_ft_face(ftFace, 0);
    }
     */
    
    cairo_font_face_t *ff = findFontFace( ui->fontFamily->is_set ? ui->fontFamily->s_value : "Forum", NULL);
    cairo_set_font_face( cr, ff );

/*
    cairo_select_font_face (cr, "Sans",
                            CAIRO_FONT_SLANT_NORMAL,
                            CAIRO_FONT_WEIGHT_NORMAL);
*/
    
    double fontSize = 14.0;
    
    if(ui->fontSize->is_set) fontSize = ui->fontSize->f_value * ui->calculated.scale;
    
    // printf("FONT SIZE %f", fontSize);
    
    cairo_set_font_size(cr, fontSize);
    
    cairo_text_extents_t extents;
    cairo_text_extents (cr, ui->text->s_value, &extents);
    
    // printf("Text box size : %f %f \n", extents.width, extents.height);
    
    if(ui->color->is_set) {
        UIColorType *c = ui->color;
        cairo_set_source_rgba(cr, c->r/255.0, c->g/255.0, c->b/255.0, getGlobalAlpha(c->a/255.0));
    } else {
        
       cairo_set_source_rgba(cr, 0,0,0,getGlobalAlpha(1.0));
    }
    // cairo_set_source_rgba(cr, 0,0,0,1);
    // cairo_show_text (cr, utf8);
    // cairo_show_text(cr, ui->text->s_value);
    cairo_translate(cr, 0,fontSize);
    
    
    void (*text_fn) (cairo_t *cr, const char *utf8);
    
    // cairo_text_path (cr, ui->text->s_value);
    if(ui->shadowRadius->is_set) {
        // cairo_text_path (cr, ui->text->s_value);
        text_fn = cairo_text_path;
    } else {
        text_fn = cairo_show_text;
    }
       //  cairo_show_text(cr, ui->text->s_value);
        
        char *str = strdup( ui->text->s_value  );
        char *final_string  = strdup("");
        char *old_final_string  = NULL;
        char *old_to_print = NULL;
        char *token = NULL;
    
        // cairo_text_extents_t extents;
        
        double x_pos = 0;
        double y_pos = 0;
        double start_x = 0;
        double last_good_width=0;
    
        token = strtok(str, " ");
        while(token) {
            char *toPrint = stradd(token, " ");
            cairo_text_extents (cr, toPrint, &extents);
            
            if( (last_good_width ==0) || (x_pos + extents.x_advance) < ui->innerWidth->pixels) {
                final_string = stradd( final_string, toPrint);
                
                // save how long is the text right now...
                last_good_width = x_pos + extents.x_advance;
                
                if( old_final_string) free(old_final_string);
                if( old_to_print) free(old_to_print);
                
                old_final_string = NULL;
                old_to_print = NULL;

                // cairo_move_to(cr, x_pos, y_pos);
                // text_fn(cr, toPrint);
                x_pos += extents.x_advance;
            } else {
                
                // text is too long, print the final_string and move pointer
                // to next line

                start_x = 0;
                if( ui->align->is_set) {
                    if(strcmp(ui->align->s_value,"center") == 0) {
                        start_x += (ui->innerWidth->pixels - last_good_width) * 0.5;
                    }
                    if(strcmp(ui->align->s_value,"right") == 0) {
                        start_x += (ui->innerWidth->pixels - last_good_width);
                    }
                }
                
                
                cairo_move_to(cr, start_x, y_pos);
                text_fn(cr, final_string);
                y_pos += fontSize;
                // move the part of the string which did not fit to previous line as the current
                // active string "final_string"
                final_string = strdup(toPrint);
                if( old_final_string) free(old_final_string);
                old_final_string = NULL;
                
                last_good_width = extents.x_advance;
                x_pos = extents.x_advance;
            }
            
            // save old values
            old_final_string = final_string;
            old_to_print = toPrint;
            

            
            // printf("-> %s , x_pos : %f width : %f  advance : %f wid : %f \n", toPrint, x_pos, ui->innerWidth->pixels, extents.x_advance, extents.width);
            token = strtok(NULL, " ");
        }
        // if we have something to draw, draw the rest
        if(last_good_width > 0) {
            start_x = 0;
            if( ui->align->is_set) {
                if(strcmp(ui->align->s_value,"center") == 0) {
                    start_x += (ui->innerWidth->pixels - last_good_width) * 0.5;
                }
                if(strcmp(ui->align->s_value,"right") == 0) {
                    start_x += (ui->innerWidth->pixels - last_good_width);
                }
            }
            // y_pos += fontSize;
            cairo_move_to(cr, start_x, y_pos);
            text_fn(cr, final_string);
            y_pos += fontSize;
        }
        // free temporary string pointers
        if( old_final_string) free(old_final_string);
        if( old_to_print) free(old_to_print);
    
    if(ui->shadowRadius->is_set) {
        evg_apply_shadow( cr, ui, cairo_fill );
        //cairo_fill(cr);
    }
    cairo_fill(cr);
    
    // printf("Rendered text %s \n", ui->text->s_value);
    
}

// Credit: nanosvg, Mikko Mononen memon@inside.org
//
static int __isspace(char c)
{
    return strchr(" \t\n\v\f\r", c) != 0;
}

static int __isdigit(char c)
{
    return strchr("0123456789", c) != 0;
}

static int __isnum(char c)
{
    return strchr("0123456789+-.eE", c) != 0;
}


static const char* __parseNumber(const char* s, char* it, const int size)
{
    const int last = size-1;
    int i = 0;
    
    // sign
    if (*s == '-' || *s == '+') {
        if (i < last) it[i++] = *s;
        s++;
    }
    // integer part
    while (*s && __isdigit(*s)) {
        if (i < last) it[i++] = *s;
        s++;
    }
    if (*s == '.') {
        // decimal point
        if (i < last) it[i++] = *s;
        s++;
        // fraction part
        while (*s && __isdigit(*s)) {
            if (i < last) it[i++] = *s;
            s++;
        }
    }
    // exponent
    if (*s == 'e' || *s == 'E') {
        if (i < last) it[i++] = *s;
        s++;
        if (*s == '-' || *s == '+') {
            if (i < last) it[i++] = *s;
            s++;
        }
        while (*s && __isdigit(*s)) {
            if (i < last) it[i++] = *s;
            s++;
        }
    }
    it[i] = '\0';
    
    return s;
}

static const char* __getNextPathItem(const char* s, char* it)
{
    it[0] = '\0';
    // Skip white spaces and commas
    while (*s && (__isspace(*s) || *s == ',')) s++;
    if (!*s) return s;
    if (*s == '-' || *s == '+' || *s == '.' || __isdigit(*s)) {
        s = __parseNumber(s, it, 64);
    } else {
        // Parse command
        it[0] = *s++;
        it[1] = '\0';
        return s;
    }
    
    return s;
}

static int __getArgsPerCommand(char cmd)
{
    switch (cmd) {
        case 'v':
        case 'V':
        case 'h':
        case 'H':
            return 1;
        case 'm':
        case 'M':
        case 'l':
        case 'L':
        case 't':
        case 'T':
            return 2;
        case 'q':
        case 'Q':
        case 's':
        case 'S':
            return 4;
        case 'c':
        case 'C':
            return 6;
        case 'a':
        case 'A':
            return 7;
    }
    return 0;
}

// Ported from: https://github.com/memononen/nanosvg/blob/master/src/nanosvg.h

static float __sqr(float x) { return x*x; }
static float __vmag(float x, float y) { return sqrtf(x*x + y*y); }

static float __vecrat(float ux, float uy, float vx, float vy)
{
    return (ux*vx + uy*vy) / (__vmag(ux,uy) * __vmag(vx,vy));
}

static float __vecang(float ux, float uy, float vx, float vy)
{
    float r = __vecrat(ux,uy, vx,vy);
    if (r < -1.0f) r = -1.0f;
    if (r > 1.0f) r = 1.0f;
    return ((ux*vy < uy*vx) ? -1.0f : 1.0f) * acosf(r);
}

static void __xformPoint(float* dx, float* dy, float x, float y, float* t)
{
    *dx = x*t[0] + y*t[2] + t[4];
    *dy = x*t[1] + y*t[3] + t[5];
}

static void __xformVec(float* dx, float* dy, float x, float y, float* t)
{
    *dx = x*t[0] + y*t[2];
    *dy = x*t[1] + y*t[3];
}

static void __pathArcTo( cairo_t *cr, float* cpx, float* cpy, float* args, int rel)
{
    // Ported from canvg (https://code.google.com/p/canvg/)
    float rx, ry, rotx;
    float x1, y1, x2, y2, cx, cy, dx, dy, d;
    float x1p, y1p, cxp, cyp, s, sa, sb;
    float ux, uy, vx, vy, a1, da;
    float x, y, tanx, tany, a, px = 0, py = 0, ptanx = 0, ptany = 0, t[6];
    float sinrx, cosrx;
    int fa, fs;
    int i, ndivs;
    float hda, kappa;
    
    rx = fabsf(args[0]);				// y radius
    ry = fabsf(args[1]);				// x radius
    rotx = args[2] / 180.0f * M_PI;		// x rotation engle
    fa = fabsf(args[3]) > 1e-6 ? 1 : 0;	// Large arc
    fs = fabsf(args[4]) > 1e-6 ? 1 : 0;	// Sweep direction
    x1 = *cpx;							// start point
    y1 = *cpy;
    if (rel) {							// end point
        x2 = *cpx + args[5];
        y2 = *cpy + args[6];
    } else {
        x2 = args[5];
        y2 = args[6];
    }
    
    dx = x1 - x2;
    dy = y1 - y2;
    d = sqrtf(dx*dx + dy*dy);
    if (d < 1e-6f || rx < 1e-6f || ry < 1e-6f) {
        // The arc degenerates to a line
        
        cairo_line_to( cr, x2, y2);
        
        *cpx = x2;
        *cpy = y2;
        return;
    }
    
    sinrx = sinf(rotx);
    cosrx = cosf(rotx);
    
    // Convert to center point parameterization.
    // http://www.w3.org/TR/SVG11/implnote.html#ArcImplementationNotes
    // 1) Compute x1', y1'
    x1p = cosrx * dx / 2.0f + sinrx * dy / 2.0f;
    y1p = -sinrx * dx / 2.0f + cosrx * dy / 2.0f;
    d = __sqr(x1p)/__sqr(rx) + __sqr(y1p)/__sqr(ry);
    if (d > 1) {
        d = sqrtf(d);
        rx *= d;
        ry *= d;
    }
    // 2) Compute cx', cy'
    s = 0.0f;
    sa = __sqr(rx)*__sqr(ry) - __sqr(rx)*__sqr(y1p) - __sqr(ry)*__sqr(x1p);
    sb = __sqr(rx)*__sqr(y1p) + __sqr(ry)*__sqr(x1p);
    if (sa < 0.0f) sa = 0.0f;
    if (sb > 0.0f)
        s = sqrtf(sa / sb);
    if (fa == fs)
        s = -s;
    cxp = s * rx * y1p / ry;
    cyp = s * -ry * x1p / rx;
    
    // 3) Compute cx,cy from cx',cy'
    cx = (x1 + x2)/2.0f + cosrx*cxp - sinrx*cyp;
    cy = (y1 + y2)/2.0f + sinrx*cxp + cosrx*cyp;
    
    // 4) Calculate theta1, and delta theta.
    ux = (x1p - cxp) / rx;
    uy = (y1p - cyp) / ry;
    vx = (-x1p - cxp) / rx;
    vy = (-y1p - cyp) / ry;
    a1 = __vecang(1.0f,0.0f, ux,uy);	// Initial angle
    da = __vecang(ux,uy, vx,vy);		// Delta angle
    
    //	if (vecrat(ux,uy,vx,vy) <= -1.0f) da = NSVG_PI;
    //	if (vecrat(ux,uy,vx,vy) >= 1.0f) da = 0;
    
    if (fa) {
        // Choose large arc
        if (da > 0.0f)
            da = da - 2*M_PI;
        else
            da = 2*M_PI + da;
    }
    
    // Approximate the arc using cubic spline segments.
    t[0] = cosrx; t[1] = sinrx;
    t[2] = -sinrx; t[3] = cosrx;
    t[4] = cx; t[5] = cy;
    
    // Split arc into max 90 degree segments.
    // The loop assumes an iteration per end point (including start and end), this +1.
    ndivs = (int)(fabsf(da) / (M_PI*0.5f) + 1.0f);
    hda = (da / (float)ndivs) / 2.0f;
    kappa = fabsf(4.0f / 3.0f * (1.0f - cosf(hda)) / sinf(hda));
    if (da < 0.0f)
        kappa = -kappa;
    
    for (i = 0; i <= ndivs; i++) {
        a = a1 + da * (i/(float)ndivs);
        dx = cosf(a);
        dy = sinf(a);
        
        __xformPoint(&x, &y, dx*rx, dy*ry, t); // position
        __xformVec(&tanx, &tany, -dy*rx * kappa, dx*ry * kappa, t); // tangent
        
        if (i > 0) {
            
            cairo_curve_to( cr, px+ptanx,py+ptany, x-tanx, y-tany, x, y);
            
            // nsvg__cubicBezTo(p, px+ptanx,py+ptany, x-tanx, y-tany, x, y);
            
        }
        
        px = x;
        py = y;
        ptanx = tanx;
        ptany = tany;
    }
    
    *cpx = x2;
    *cpy = y2;
}

static void render_svg_path( cairo_t *cr, UIStructure *ui ) {
    
    //
    double points[8];
    
    char   value_str[64];
    
    char   cmd = 'L';
    
    int    max_cnt = 1000; // path max length... for testing...
    
    char   *s = ui->svgPath->s_value;
    char   item[64];
    
    int    nargs = 0;
    int    rargs = 0;
    float  args[10];
    
    float  cx = 0;
    float  cy = 0;
    
    float  cx2 = 0;
    float  cy2 = 0;
    
    float  QPx[3];
    float  QPy[3];
    float  Cpx[4];
    float  Cpy[4];
    /*
     void
     cairo_path_extents (cairo_t *cr,
     double *x1,
     double *y1,
     double *x2,
     double *y2);
    */
    
    while (*s) {
        
        s = __getNextPathItem(s, item);
        if (!*item) break;
        
        // printf("Item %s\n", item );
        
        if (__isnum(item[0])) {
            if (nargs < 10) {
                args[nargs++] = (float)atof(item);
            }

            // number of commands has achieved the required...
            if (nargs >= rargs) {
                
                //
                switch (cmd) {
                    case 'm':
                        cairo_move_to( cr, cx + args[0], cy + args[1] );
                        cx = cx + args[0];
                        cy = cy + args[1];
                        cmd = 'l';
                        rargs = 2;
                        cx2 = cx;
                        cy2 = cy;
                        break;
                    case 'M':
                        cairo_move_to( cr, args[0], args[1] );
                        cx = args[0];
                        cy = args[1];
                        cmd = 'L';
                        rargs = 2;
                        cx2 = cx;
                        cy2 = cy;
                        break;
                        
                    case 'l':
                        cairo_line_to( cr, cx + args[0], cy + args[1] );
                        cx = cx + args[0];
                        cy = cy + args[1];
                        cx2 = cx;
                        cy2 = cy;
                        break;
                    case 'L':
                        cairo_line_to( cr, args[0], args[1] );
                        cx = args[0];
                        cy = args[1];
                        cx2 = cx;
                        cy2 = cy;
                        break;

                    case 'h':
                        cairo_line_to( cr, cx + args[0], cy );
                        cx = cx + args[0];
                        cx2 = cx;
                        break;
                        
                    case 'H':
                        cairo_line_to( cr, args[0], cy );
                        cx =  args[0];
                        cx2 = cx;
                        break;

                    case 'v':
                        cairo_line_to( cr, cx, cy + args[0] );
                        cy = cy + args[0];
                        cy2 = cy;
                        break;
                        
                    case 'V':
                        cairo_line_to( cr, cx, args[0] );
                        cy =  args[0];
                        cx2 = cx;
                        break;

                    case 'c':
                        
                        cairo_curve_to( cr, cx + args[0], cy + args[1]
                                          , cx + args[2], cy + args[3]
                                          , cx + args[4], cy + args[5]
                                       );
                        cx2 = cx + args[2];
                        cy2 = cy + args[3];
                        cx  = cx + args[4];
                        cy  = cy + args[5];
                        break;
                        
                    case 'C':
                        
                        cairo_curve_to( cr,  args[0],  args[1]
                                       ,  args[2],     args[3]
                                       ,  args[4],     args[5]
                                       );
                        cx2 = args[2];
                        cy2 = args[3];
                        cx  = args[4];
                        cy  = args[5];
                        break;

                    case 's':
                        
                        cairo_curve_to( cr, 2*cx - cx2, 2*cy - cy2  // cx + (cx - cx2), cy + (cy - cy2)
                                       , cx + args[0], cy + args[1]
                                       , cx + args[2], cy + args[3]
                                       );
                        cx2 = cx + args[0];
                        cy2 = cy + args[1];
                        cx  = cx + args[2];
                        cy  = cy + args[3];
                        break;
                        
                    case 'S':
                        
                        cairo_curve_to( cr,  2*cx - cx2,  2*cy - cy2
                                       ,  args[0],     args[1]
                                       ,  args[2],     args[3]
                                       );
                        cx2 = args[0];
                        cy2 = args[1];
                        cx  = args[2];
                        cy  = args[3];
                        break;
                        
/*
 Conversion of Cubic to Quadratic curve:
 
 CP0 = QP0
 CP3 = QP2
 
 CP1 = QP0 + 2/3 *(QP1-QP0)
 CP2 = QP2 + 2/3 *(QP1-QP2)
 */
                    case 'q':
                        
                        QPx[0] = cx;
                        QPy[0] = cy;
                        
                        QPx[1] = cx + args[0];
                        QPy[1] = cy + args[1];
                        
                        QPx[2] = cx + args[2];
                        QPy[2] = cy + args[3];
                        
                        Cpx[0] = QPx[0];
                        Cpy[0] = QPx[0];
                        
                        Cpx[1] = QPx[0] + (2.0 / 3.0) * (QPx[1] - QPx[0]);
                        Cpy[1] = QPy[0] + (2.0 / 3.0) * (QPy[1] - QPy[0]);
                        
                        Cpx[2] = QPx[2] + (2.0 / 3.0) * (QPx[1] - QPx[2]);
                        Cpy[2] = QPy[2] + (2.0 / 3.0) * (QPy[1] - QPy[2]);
                        
                        Cpx[3] = QPx[2];
                        Cpy[3] = QPx[2];
                        
                        cairo_curve_to( cr, Cpx[1], Cpy[1],
                                            Cpx[2], Cpy[2],
                                            Cpx[3], Cpy[3]
                                       );
                        
                        cx2 = Cpx[2];
                        cy2 = Cpy[2];
                        cx  = Cpx[3];
                        cy  = Cpy[3];
                        break;
                        
                    case 'Q':
                        QPx[0] = cx;
                        QPy[0] = cy;
                        
                        QPx[1] = args[0];
                        QPy[1] = args[1];
                        
                        QPx[2] = args[2];
                        QPy[2] = args[3];
                        
                        Cpx[0] = QPx[0];
                        Cpy[0] = QPx[0];
                        
                        Cpx[1] = QPx[0] + (2.0 / 3.0) * (QPx[1] - QPx[0]);
                        Cpy[1] = QPy[0] + (2.0 / 3.0) * (QPy[1] - QPy[0]);
                        
                        Cpx[2] = QPx[2] + (2.0 / 3.0) * (QPx[1] - QPx[2]);
                        Cpy[2] = QPy[2] + (2.0 / 3.0) * (QPy[1] - QPy[2]);
                        
                        Cpx[3] = QPx[2];
                        Cpy[3] = QPx[2];
                        
                        cairo_curve_to( cr, Cpx[0], Cpy[0],
                                       Cpx[1], Cpy[1],
                                       Cpx[2], Cpy[2]
                                       );
                        

                        cx2 = Cpx[1];
                        cy2 = Cpy[1];
                        cx  = Cpx[2];
                        cy  = Cpy[2];

                        break;
                    case 'T':

                        QPx[0] = cx;
                        QPy[0] = cy;
                        
                        QPx[1] = 2*cx - cx2;
                        QPy[1] = 2*cy - cy2;
                        
                        QPx[2] = args[0];
                        QPy[2] = args[1];
                        
                        Cpx[0] = QPx[0];
                        Cpy[0] = QPx[0];
                        
                        Cpx[1] = QPx[0] + (2.0 / 3.0) * (QPx[1] - QPx[0]);
                        Cpy[1] = QPy[0] + (2.0 / 3.0) * (QPy[1] - QPy[0]);
                        
                        Cpx[3] = QPx[2];
                        Cpy[3] = QPx[2];
                        
                        cairo_curve_to( cr, Cpx[0], Cpy[0],
                                       Cpx[1], Cpy[1],
                                       Cpx[2], Cpy[2]
                                       );
                        
                        
                        cx2 = Cpx[1];
                        cy2 = Cpy[1];
                        cx  = Cpx[2];
                        cy  = Cpy[2];
                        
                        break;
                        
                        
                        
                    case 't':
                        QPx[0] = cx;
                        QPy[0] = cy;
                        
                        QPx[1] = 2*cx - cx2;
                        QPy[1] = 2*cy - cy2;
                        
                        QPx[2] = cx + args[0];
                        QPy[2] = cy + args[1];
                        
                        Cpx[0] = QPx[0];
                        Cpy[0] = QPx[0];
                        
                        Cpx[1] = QPx[0] + (2.0 / 3.0) * (QPx[1] - QPx[0]);
                        Cpy[1] = QPy[0] + (2.0 / 3.0) * (QPy[1] - QPy[0]);
                        
                        Cpx[3] = QPx[2];
                        Cpy[3] = QPx[2];
                        
                        cairo_curve_to( cr, Cpx[0], Cpy[0],
                                       Cpx[1], Cpy[1],
                                       Cpx[2], Cpy[2]
                                       );
                        
                        
                        cx2 = Cpx[1];
                        cy2 = Cpy[1];
                        cx  = Cpx[2];
                        cy  = Cpy[2];

                        break;
                    case 'A':
                    case 'a':
                        // static void __pathArcTo( cairo_t *cr, float* cpx, float* cpy, float* args, int rel)
                        
                        __pathArcTo(cr, &cx, &cy, args, cmd == 'a' ? 1 : 0);
                        cx2 = cx;
                        cy2 = cy;

                        break;
                    default:
                        if (nargs >= 2) {
                            cx = args[nargs-2];
                            cy = args[nargs-1];
                            cx2 = cx;
                            cy2 = cy;
                        }
                        break;
                }
                nargs = 0;
            }
            
            
            
        } else {
            cmd = item[0];
            rargs = __getArgsPerCommand(cmd);
            
            if(cmd == 'z' || cmd == 'Z') {
                cairo_close_path( cr );
            }
        }
        
            
        
        // REMOVE:
        if(max_cnt-- <= 0) break;
    }
    
    
}

// SEE:
// https://www.cairographics.org/samples/

static void create_initial_path( cairo_t *cr, UIStructure *ui) {
    if(ui->svgPath->is_set) {
        render_svg_path( cr, ui );
        /*
         cairo_path_extents
         */
        
        double x1,x2,y1,y2;
        cairo_path_extents(cr, &x1,&y1, &x2, &y2);
        // clear path...
        double scale_x = (x2-x1);
        double scale_y = (y2-y1);
        if(scale_x != 0 && scale_y != 0) {
            
            cairo_path_t *path_copy = cairo_copy_path(cr);
            
            cairo_new_path( cr );
            cairo_save(cr);
            cairo_scale( cr, ui->calculated.render_width/scale_x, ui->calculated.render_height/scale_y);
            
            // printf("Should scale by %f\n", ui->calculated.render_width/scale_x);
            
            cairo_translate( cr, -x1, -y1 );
            
            cairo_append_path(cr, path_copy);
            
            cairo_restore(cr);
        }
    } else {
        if(ui->borderRadius->is_set) {
          // double scaling = ui->scale->is_set ? ui->scale->f_value : 1;
          create_rounded_rect( cr, 0,0, ui->calculated.render_width, ui->calculated.render_height, ui->borderRadius->pixels);
            
        } else {
            cairo_rectangle(cr, 0, 0, ui->calculated.render_width, ui->calculated.render_height);
        }
    }
}

static void render_ui(cairo_t *cr, UIStructure *ui) {
    
    if(imageList == NULL) {
        imageList = createList();
    }
    
    int has_clip = 0;
    int has_painted = 0;
    cairo_save(cr);
    // position the surface
    cairo_translate(cr, ui->calculated.x, ui->calculated.y);

    /* Apply rotation if set - rotate around the center of the element */
    if(ui->rotate->is_set) {
        /* Move to center, rotate, move back */
        double cx = ui->calculated.render_width / 2.0;
        double cy = ui->calculated.render_height / 2.0;
        cairo_translate(cr, cx, cy);
        cairo_rotate(cr, ui->rotate->f_value * (M_PI / 180.0));  /* Convert degrees to radians */
        cairo_translate(cr, -cx, -cy);
    }

    if(ui->scale->is_set) {
      cairo_scale(cr, ui->calculated.scale, ui->scale->f_value);
    }
    
    
    if(ui->opacity->is_set) {
        printf("Pushing alpha %f \n ", ui->opacity->f_value);
        pushGlobalAlpha( ui->opacity->f_value );
    }
    
    /*
     cairo_pattern_t *pat;
     
     pat = cairo_pattern_create_linear (0.0, 0.0,  0.0, 256.0);
     cairo_pattern_add_color_stop_rgba (pat, 1, 0, 0, 0, 1);
     cairo_pattern_add_color_stop_rgba (pat, 0, 1, 1, 1, 1);
     cairo_rectangle (cr, 0, 0, 256, 256);
     cairo_set_source (cr, pat);
     cairo_fill (cr);
     cairo_pattern_destroy (pat);
    */
    
    /*
    if(ui->overflow->is_set && (strcmp(ui->overflow->s_value, "hidden")==0)) {
        create_initial_path( cr, ui );
        cairo_clip (cr);
        has_clip = 1;
    }
     */
    
    if(!has_painted && ui->radialGradient->is_set && ui->radialGradient->next) {
        
        // printf("Might paint  radialGradient \n");
        has_painted = 1;
        cairo_pattern_t *pat;
        UIColorStop *stop1 = ui->linearGradient;
        UIColorStop *stop2 = ui->linearGradient->next;

        pat = cairo_pattern_create_radial (ui->calculated.render_width/2,  ui->calculated.render_height/2,  0,
                                           ui->calculated.render_width/2,  ui->calculated.render_height/2,  ui->calculated.render_width/2.0);
        
        UIColorStop *stop = ui->radialGradient;
        while(stop) {
            cairo_pattern_add_color_stop_rgba (pat, stop->percentage / 100.00, stop->color->r / 255.0,
                                               stop->color->g / 255.0,
                                               stop->color->b / 255.0,
                                               getGlobalAlpha( stop->color->a / 255.0 ) );
            stop = stop->next;
        }
        
        cairo_set_source (cr, pat);
        
        create_initial_path( cr, ui );

        /*
        if(ui->borderRadius->is_set) {
            create_rounded_rect( cr, 0,0, ui->calculated.render_width, ui->calculated.render_height, ui->borderRadius->pixels);
        } else {
            cairo_rectangle(cr, 0, 0, ui->calculated.render_width, ui->calculated.render_height);
        }
         */
        cairo_clip (cr);
        cairo_mask(cr, pat);
        
    }
    
    if(!has_painted && ui->linearGradient->is_set && ui->linearGradient->next) {
        
        has_painted = 1;
        cairo_pattern_t *pat;
        UIColorStop *stop1 = ui->linearGradient;
        UIColorStop *stop2 = ui->linearGradient->next;
        
        double rads = M_PI * (stop1->degree - 90)/180;
        double i = cos(rads);
        double j = sin(rads);
        
        double half_x = ui->calculated.render_width / 2;
        double half_y = ui->calculated.render_height / 2;
        
        if( (j > 0) ) {
            
            if( i > 0 ) {
                double v1_x = -half_x;
                double v1_y = -half_y;
                double v2_x =  half_x;
                double v2_y =  half_y;
                
                double dotp1 = v1_x * (-i) + v1_y * (-j);
                double dotp2 = v2_x * (i) + v2_y * (j);
                double proj1_x = -i * dotp1 +half_x;
                double proj1_y = -j * dotp1 +half_y;
                double proj2_x = i * dotp2 +half_x;
                double proj2_y = j * dotp2 +half_y;
                
                // printf("angled pattern 1 %f %f %f %f \n", proj1_x, proj1_y, proj2_x, proj2_y);
                
                pat = cairo_pattern_create_linear (proj1_x, proj1_y, proj2_x, proj2_y); // only vertical for now...
            } else {

                double v1_x =  half_x;
                double v1_y = -half_y;
                double v2_x = -half_x;
                double v2_y =  half_y;
                
                double dotp1 = v1_x * (-i) + v1_y * (-j);
                double dotp2 = v2_x * (i) + v2_y * (j);
                double proj1_x = -i * dotp1 +half_x;
                double proj1_y = -j * dotp1 +half_y;
                double proj2_x = i * dotp2 +half_x;
                double proj2_y = j * dotp2 +half_y;
                
                // printf("angled pattern 2 %f %f %f %f \n", proj1_x, proj1_y, proj2_x, proj2_y);
                
                pat = cairo_pattern_create_linear (proj1_x, proj1_y, proj2_x, proj2_y); // only vertical for now...
            }
            
        } else {
            
            
            if( i > 0 ) {
                double v1_x = -half_x;
                double v1_y = half_y;
                double v2_x = half_x;
                double v2_y = -half_y;
                
                double dotp1 = v1_x * (-i) + v1_y * (-j);
                double dotp2 = v2_x * (i) + v2_y * (j);
                double proj1_x = -i * dotp1 +half_x;
                double proj1_y = -j * dotp1 +half_y;
                double proj2_x = i * dotp2 +half_x;
                double proj2_y = j * dotp2 +half_y;
                
                // printf("angled pattern 3 %f %f %f %f \n", proj1_x, proj1_y, proj2_x, proj2_y);
                
                pat = cairo_pattern_create_linear (proj1_x, proj1_y, proj2_x, proj2_y); // only vertical for now...
            } else {
                
                double v1_x =  half_x;
                double v1_y =  half_y;
                double v2_x =  -half_x;
                double v2_y =  -half_y;
                
                double dotp1 = v1_x * (-i) + v1_y * (-j);
                double dotp2 = v2_x * (i) + v2_y * (j);
                double proj1_x = -i * dotp1 +half_x;
                double proj1_y = -j * dotp1 +half_y;
                double proj2_x = i * dotp2 +half_x;
                double proj2_y = j * dotp2 +half_y;
                
                // printf("angled pattern 4 %f %f %f %f \n", proj1_x, proj1_y, proj2_x, proj2_y);
                
                pat = cairo_pattern_create_linear (proj1_x, proj1_y, proj2_x, proj2_y); // only vertical for now...
            }
            
            // others are not processed right now...
            // pat = cairo_pattern_create_linear (0.0, 0.0,  0.0, ui->calculated.render_height); // only vertical for now...
        }
        

        UIColorStop *stop = ui->linearGradient;
        while(stop) {
           cairo_pattern_add_color_stop_rgba (pat, stop->percentage / 100.00, stop->color->r / 255.0,
                                                   stop->color->g / 255.0,
                                                   stop->color->b / 255.0,
                                                   getGlobalAlpha( stop->color->a / 255.0 ) );
            stop = stop->next;
        }

        cairo_set_source (cr, pat);
        
        create_initial_path( cr, ui );
        /*
        if(ui->borderRadius->is_set) {
            create_rounded_rect( cr, 0,0, ui->calculated.render_width, ui->calculated.render_height, ui->borderRadius->pixels);
        } else {
            cairo_rectangle(cr, 0, 0, ui->calculated.render_width, ui->calculated.render_height);
        }
        */
        // cairo_fill(cr);
        if(ui->shadowRadius->is_set) {
            evg_apply_shadow( cr, ui, cairo_fill );
            cairo_fill(cr);
        } else {
            cairo_fill(cr);
        }
        
    }
    if(!has_painted && ui->backgroundColor->is_set) {
        // printf("*** should render something **** \n");
        
        /*
        cairo_set_source_rgba(cr, ui->backgroundColor->r/255.00,
                                  ui->backgroundColor->g/255.00,
                                  ui->backgroundColor->b/255.00,
                                  getGlobalAlpha( ui->backgroundColor->a/255.00 ) );
       
        */
        
        double calc_f = getGlobalAlpha( ui->backgroundColor->a / 255.00 );
        
        printf( "%f vs %f vs %f \n", 0.5*ui->backgroundColor->a/255.00, ui->backgroundColor->a/255.00, calc_f  );
        
        cairo_set_source_rgba(cr, ui->backgroundColor->r/255.00,
                              ui->backgroundColor->g/255.00,
                              ui->backgroundColor->b/255.00,
                              calc_f );
        
        create_initial_path( cr, ui );
        
        /*
        if(ui->svgPath->is_set) {
            render_svg_path( cr, ui );
            double x1,x2,y1,y2;
            cairo_path_extents(cr, &x1,&y1, &x2, &y2);
            // clear path...
            double scale_x = (x2-x1);
            double scale_y = (y2-y1);
            if(scale_x != 0 && scale_y != 0) {
                
                cairo_path_t *path_copy = cairo_copy_path(cr);
                
                cairo_new_path( cr );
                
                cairo_scale( cr, ui->calculated.render_width/scale_x, ui->calculated.render_height/scale_y);
                
                printf("Should scale by %f\n", ui->calculated.render_width/scale_x);
                
                cairo_translate( cr, -x1, -y1 );
                
                cairo_append_path(cr, path_copy);
            }
        } else {
            if(ui->borderRadius->is_set) {
                create_rounded_rect( cr, 0,0, ui->calculated.render_width, ui->calculated.render_height, ui->borderRadius->pixels);

            } else {
                cairo_rectangle(cr, 0, 0, ui->calculated.render_width, ui->calculated.render_height);
            }
        }
    */

        // void evg_apply_shadow(cairo_t _context, UIStructure *ui, void (fn)(cairo_t *cr)) {
        
        if(ui->borderWidth->is_set) {
            cairo_set_line_width( cr, ui->borderWidth->pixels);
            if(ui->shadowRadius->is_set) {
                evg_apply_shadow( cr, ui, cairo_fill );
                if(ui->overflow->is_set && (strcmp(ui->overflow->s_value, "hidden")==0)) {
                    cairo_clip_preserve (cr);
                }
                cairo_fill_preserve(cr);
            } else {
                if(ui->overflow->is_set && (strcmp(ui->overflow->s_value, "hidden")==0)) {
                    cairo_clip_preserve (cr);
                }
                cairo_fill_preserve(cr);
            }
            if(ui->borderColor->is_set) {
                cairo_set_source_rgba(cr, ui->borderColor->r/255.00,
                                      ui->borderColor->g/255.00,
                                      ui->borderColor->b/255.00,
                                      getGlobalAlpha( ui->borderColor->a/255.00 ) );
                cairo_stroke(cr);
            } else {
                if(ui->color->is_set) {
                    cairo_set_source_rgba(cr, ui->color->r/255.00,
                                          ui->color->g/255.00,
                                          ui->color->b/255.00,
                                          getGlobalAlpha(ui->color->a/255.00 ) );
                    cairo_stroke(cr);
                } else {
                    cairo_set_source_rgba(cr, 0.0,0.0,0.0,getGlobalAlpha(1.0) );
                    cairo_stroke(cr);
                }
            }
            
        } else {
            if(ui->shadowRadius->is_set) {
                evg_apply_shadow( cr, ui, cairo_fill );
                if(ui->overflow->is_set && (strcmp(ui->overflow->s_value, "hidden")==0)) {
                    cairo_clip_preserve (cr);
                }
                cairo_fill(cr);
                printf("--- basic fill \n");
            } else {
                if(ui->overflow->is_set && (strcmp(ui->overflow->s_value, "hidden")==0)) {
                    cairo_clip_preserve (cr);
                }
                cairo_fill(cr);
            }
        }
        

    }
    
    
    if(ui->imageUrl->is_set) {
        // slow if create every time new surface
        char *img_name = concat("/var/www", ui->imageUrl->s_value);
        
        cairo_surface_t *png_surface = NULL;
        
        LinkedListNode *old_surface = List_find(imageList, img_name);
        
        if(old_surface == NULL) {
            png_surface = cairo_image_surface_create_from_png(img_name);
            
            /* Debug: Check if image loaded successfully */
            cairo_status_t status = cairo_surface_status(png_surface);
            if (status != CAIRO_STATUS_SUCCESS) {
                printf("ERROR: Failed to load image '%s': %s\n", 
                       img_name, cairo_status_to_string(status));
            } else {
                printf("DEBUG: Loaded image '%s' successfully\n", img_name);
            }
            
            LinkedListNode *saveItem = ListNode_Create(img_name, png_surface);
            List_push( imageList, saveItem );
        } else {
            // printf("Had old surface\n");
            png_surface = (cairo_surface_t*)old_surface->data;
        }
        // cairo_surface_t *png_surface = cairo_image_surface_create_from_png(img_name);
        if(png_surface != NULL && cairo_surface_status(png_surface) == CAIRO_STATUS_SUCCESS) {
            int w = cairo_image_surface_get_width(png_surface);
            int h = cairo_image_surface_get_height(png_surface);
            
            // printf("Image %s %i x %i \n", img_name, w,h);
            
            if (w > 0 && h > 0) {
                double scale_f = ui->calculated.render_width/w;
            
            
            cairo_scale (cr, scale_f, scale_f);
            
            // evg_blur( png_surface, 4);
            
            cairo_set_source_surface (cr, png_surface, 0, 0);
            
            if(ui->shadowRadius->is_set) {
                evg_apply_shadow( cr, ui, cairo_fill );
                //cairo_fill(cr);
            }
            
            // create_initial_path( cr, ui );
            
            if(getGlobalAlpha( 1.0 ) < 1.0) {
                cairo_paint_with_alpha (cr, getGlobalAlpha( 1.0 ));
            } else {
                cairo_paint (cr);
            }
            
            } /* end if (w > 0 && h > 0) */
        }
    }
    
    if(ui->text->is_set && (strcmp(ui->tagName, "Label")==0)) {
        // printf("*** text %s ****\n", ui->text->s_value);
        render_text(cr, ui );
    }

    
    // cairo_stroke_preserve -> preserves the current path
    // https://www.cairographics.org/manual/cairo-cairo-t.html#cairo-stroke-preserve
    
    UIStructure* childNode = ui->firstChild;
    
    while(childNode) {
        render_ui( cr, childNode );
        childNode = childNode->nextSibling;
    }
    
    if(has_clip) {
        // cairo_reset_clip(cr);
    }
    cairo_restore(cr);
    
    if(ui->opacity->is_set) {
        printf("Popping alpha %f \n ", ui->opacity->f_value);
        popGlobalAlpha();
    }
    
}

// creates the surface... does not destroy it though...
static void draw_ui_to_surface( UIStructure *node_tree) {
    
    if(surface != NULL) {
        cairo_destroy(cr);
        cairo_surface_destroy(surface);
    }
    
    surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, video_buf_width, video_buf_height);
    cr = cairo_create(surface);
    
    /* Clear the surface with white background */
    cairo_set_source_rgb(cr, 1.0, 1.0, 1.0);
    cairo_paint(cr);
    
    render_ui( cr, node_tree );
    
    cairo_surface_flush(surface);
    
    /* Debug: save specific frames as PNG to verify rendering */
    static int frame_count = 0;
    if (frame_count == 0) {
        cairo_surface_write_to_png(surface, "debug_frame_000.png");
        printf("DEBUG: Saved frame 0 to debug_frame_000.png\n");
    } else if (frame_count == 100) {
        cairo_surface_write_to_png(surface, "debug_frame_100.png");
        printf("DEBUG: Saved frame 100 to debug_frame_100.png\n");
    } else if (frame_count == 250) {
        cairo_surface_write_to_png(surface, "debug_frame_250.png");
        printf("DEBUG: Saved frame 250 to debug_frame_250.png\n");
    }
    frame_count++;
    
}

static void draw_ui_to_pdf(UIStructure *node_tree, char *outputFileName) {
    
    if(surface != NULL) {
        cairo_destroy(cr);
        cairo_surface_destroy(surface);
    }
    
    surface = cairo_pdf_surface_create(outputFileName, 800, 1200);
    cr = cairo_create(surface);
  
    // pango_draw_test(cr);
    render_ui( cr, node_tree );
    
    
    
    
    cairo_show_page(cr);
    cairo_surface_flush(surface);
    
    
    
    cairo_destroy(cr);
    cairo_surface_destroy(surface);
    
}
static void test_xml(char *filename, char *outputFileName) {
    xmlDoc         *document;
    xmlNode        *root, *first_child, *node;
    xmlChar        *value;
    
    document = xmlReadFile(filename, NULL, 0);
    root = xmlDocGetRootElement(document);
    if(!root) {
        return;
    }
    fprintf(stdout, "Root is <%s> (%i)\n", root->name, root->type);
    
    
    UIStructure *node_tree = parseXMLNodes(root, NULL);
    // test_walk_tree( node_tree );
    
    UIStructure *container = UIStructure_New();
    
    container->innerWidth->pixels = 800;
    container->innerHeight->pixels = 1200;
    
    calculateUIStructureLayout( node_tree, container, UIRenderPosition_With(0,0,1) );
    
    printf("Calculated and Done \n");
    
    printf("size of the root %f x %f \n", node_tree->calculated.width, node_tree->calculated.height );
    printf("size of the firstChild %f x %f \n", node_tree->firstChild->calculated.width, node_tree->firstChild->calculated.height );
    printf("size of the lastChild %f x %f \n", node_tree->lastChild->calculated.width, node_tree->lastChild->calculated.height );
    printf("position of the lastChild (%f,%f) \n", node_tree->lastChild->calculated.x, node_tree->lastChild->calculated.y );
    
    draw_ui_to_pdf(node_tree, outputFileName);
    
    return;
}


void renderXMLToSurface(char *xmlStr) {
    xmlDoc         *document;
    xmlNode        *root, *first_child, *node;
    xmlChar        *value;
    
    static int render_count = 0;
    
    document = xmlParseDoc(xmlStr);
    if (!document) {
        fprintf(stderr, "Failed to parse XML for render %d\n", render_count);
        render_count++;
        return;
    }
    root = xmlDocGetRootElement(document);
    if(!root) {
        fprintf(stderr, "No root element in XML for render %d\n", render_count);
        xmlFreeDoc(document);
        render_count++;
        return;
    }
    
    if (render_count < 3) {
        printf("DEBUG: Render %d - Root element: <%s>\n", render_count, root->name);
    }
    
    //clock_t start_time = clock();
    UIStructure *node_tree = parseXMLNodes(root, NULL);
    //clock_t end_time = clock();
    
    //printf("Parsing took : %f seconds\n", (double)(end_time - start_time) / CLOCKS_PER_SEC);
    
    UIStructure *container = UIStructure_New();
    
    // 352, 288
    
    // define the resolution used for rendering...
    container->innerWidth->pixels = video_buf_width;
    container->innerHeight->pixels = video_buf_height;
    
    // calculate layout...
    
    calculateUIStructureLayout( node_tree, container, UIRenderPosition_With(0,0,1) );
    draw_ui_to_surface(node_tree);

    /* Free memory to prevent leaks during video encoding */
    xmlFreeDoc(document);
    /* TODO: Add UIStructure_Free(node_tree) and UIStructure_Free(container) if available */
    
    render_count++;
    return;
}


static void test_xml_str(char *xmlStr) {
    xmlDoc         *document;
    xmlNode        *root, *first_child, *node;
    xmlChar        *value;
    
    document = xmlParseDoc(xmlStr);
    root = xmlDocGetRootElement(document);
    if(!root) {
        return;
    }
    fprintf(stdout, "Root is <%s> (%i)\n", root->name, root->type);
    first_child = root->children;
    for (node = first_child; node; node = node->next) {
        fprintf(stdout, "\t Child is <%s> (%i)\n", node->name, node->type);
        
        xmlAttr* attribute = node->properties;
        while(attribute)
        {

            value = xmlNodeListGetString(node->doc, attribute->children, 1);
            // fprintf(stdout, "\t Attribute %s \n", xmlChar);
            fprintf(stdout, "\t  %s = %s \n", attribute->name, value);
            //do something with value
            xmlFree(value);
            attribute = attribute->next;
        }
    }
    fprintf(stdout, "...\n");
    return;
}
// apt-get install libxml2-dev libxml2-doc
// apt-get install libxml2-dev
// http://stackoverflow.com/questions/399704/xml-parser-for-c
// gcc -Wall -o expat-test -lexpat expat-test.c


int adder(duk_context *ctx) {
    int i;
    int n = duk_get_top(ctx);
    double res = 0.0;
    
    for (i = 0; i < n; i++) {
        res += duk_to_number(ctx, i);
    }
    
    duk_push_number(ctx, res);
    return 1;
}





// this test creates video using duktape callbacks (legacy test function)
static void js_and_video_test() {
    // Now uses command line arguments via start_video_encoding()
    // start_video_encoding("../js/myTest.js", "/var/www/static/cpp/video.mp4stream");
}

static char *read_file_contents( char *fileName) {
    
    char * buffer = 0;
    long length;
    FILE * f = fopen (fileName, "rb");
    
    if (f)
    {
        fseek (f, 0, SEEK_END);
        length = ftell (f);
        fseek (f, 0, SEEK_SET);
        buffer = malloc (length);
        if (buffer)
        {
            fread (buffer, 1, length, f);
        }
        fclose (f);
    } else {
        printf("fpen failed %s\n", optarg);
        return NULL;
    }
    
    if (buffer)
    {
        // start to process your data / extract strings here...
        return buffer;
    }
    return NULL;
}

/*
 Usage:
    ./encoder -T /var/www/static/templates/ -o koe.mpg
    ./encoder -T /var/www/static/templates/

    ./encoder -js myFile.js
 
 
 
*/

int main(int argc, char **argv)
{
    int option = 0;
    int area = -1, perimeter = -1, breadth = -1, length =-1;
    
    char *inputFile = NULL;
    char *outputFile = NULL;
    char *jsFile = NULL;
    
    //Specifying the expected options
    //The two options l and b expect numbers as argument
    while ((option = getopt(argc, argv,"i:o:j:")) != -1) {
        switch (option) {
            case 'o' :
                printf("Output file: %s\n", optarg);
                outputFile = optarg;
                break;
            case 'i' :
                printf("Input XML file: %s\n", optarg);
                inputFile = optarg;
                break;
            case 'j' :
                printf("JavaScript file: %s\n", optarg);
                jsFile = optarg;
                break;
            default:
                exit(EXIT_FAILURE);
        }
    }
    
    if(jsFile && outputFile) {
        // Video encoding mode: use JavaScript file to generate frames
        printf("Starting video encoding...\n");
        start_video_encoding(jsFile, outputFile);
    } else if(inputFile && outputFile) {
        // XML to PDF mode
        test_xml(inputFile, outputFile);
    } else {
        printf("Usage:\n");
        printf("  Video encoding (JS to video):\n");
        printf("    %s -j <javascript_file> -o <output_video>\n", argv[0]);
        printf("  XML to PDF:\n");
        printf("    %s -i <input_xml> -o <output_pdf>\n", argv[0]);
        printf("\nOptions:\n");
        printf("  -j  JavaScript file for video frame generation\n");
        printf("  -i  Input XML file\n");
        printf("  -o  Output file (video or PDF)\n");
    }
    
    return 0;
    js_and_video_test();
    
    // create_cairo_pdf();
    
    // XML test below
    // test_xml("/var/www/static/cpp/test.xml");
}
