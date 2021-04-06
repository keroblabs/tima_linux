#include "generate_html.h"

////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////

static const char * html_header =
    "<html><head>\n"
    "<!-- Site made with Mobirise Website Builder v4.8.10, https://mobirise.com -->\n"
    "<meta charset=\"UTF-8\">\n"
    "<meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\">\n"
    "<meta name=\"generator\" content=\"Mobirise v4.8.10, mobirise.com\">\n"
    "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1, minimum-scale=1\">\n"
    "<link rel=\"shortcut icon\" href=\"assets/images/logo4.png\" type=\"image/x-icon\">\n"
    "<meta name=\"description\" content=\"Website Maker Description\">\n"
    "<title>%s</title>\n"
    "<link rel=\"stylesheet\" href=\"assets/tether/tether.min.css\">\n"
    "<link rel=\"stylesheet\" href=\"assets/bootstrap/css/bootstrap.min.css\">\n"
    "<link rel=\"stylesheet\" href=\"assets/bootstrap/css/bootstrap-grid.min.css\">\n"
    "<link rel=\"stylesheet\" href=\"assets/bootstrap/css/bootstrap-reboot.min.css\">\n"
    "<link rel=\"stylesheet\" href=\"assets/theme/css/style.css\">\n"
    "<link rel=\"stylesheet\" href=\"assets/mobirise/css/mbr-additional.css\" type=\"text/css\">\n"
    "</head><body>\n"
    "<section class=\"testimonials5 cid-rfUzj3vAoX\" id=\"testimonials5-y\">\n";
    //"<section class=\"testimonials5 cid-rfaxvpJEnj\" id=\"testimonials5-c\">\n";
    //"<section class=\"features8 cid-rfa7GshmJJ\" id=\"features8-3\">\n";

static const char * html_section_title =
    "<div class=\"container\">\n"
    "   <div class=\"media-container-row\">\n"
    "       <div class=\"title col-12 align-center\"><h2 class=\"pb-3 mbr-fonts-style display-2\">%s</h2></div>\n"
    "   </div>\n"
    "</div>\n";

static const char * html_division_header =
    "<div class=\"container\">\n"
    "   <div class=\"media-container-column\">\n"
    "       <div class=\"mbr-testimonial align-center col-12 col-md-10\">\n"
    "           <div class=\"panel-item\">\n"
    "               <div class=\"card-block\">\n";

static const char * html_division_box_header =
    "<div class=\"container\">\n"
    "   <div class=\"media-container-row\">\n"
    "       <div class=\"mbr-testimonial align-center col-12 col-md-10\">\n"
    "           <div class=\"panel-item\">\n"
    "               <div class=\"card-block\">\n"
    "                   <h4 class=\"card-title mbr-fonts-style display-2\">%s</h4>\n";

static const char * html_division_title =
    "                   <h2 class=\"pb-3 mbr-fonts-style display-2\">%s</h2>\n";

static const char * html_division_temperature =
    "                   <p class=\"mbr-text mbr-fonts-style mbr-white display-1\" id=\"room_temp\">%.2fº</p>\n";

static const char * html_division_extra_info =
    "                   <div class=\"title col-12 align-center\"><h2 class=\"pb-3 mbr-fonts-style display-2\">%s</h2></div>\n";

static const char * html_division_image =
    "                   <img src=\"assets/images/%s\" alt="" title=""></img>\n";

static const char * html_button_header =
    "               </div>\n"
    "               <div class=\"mbr-section-btn text-center\">\n";

static const char * html_section_button =
    "                   <a href=\"%s\" class=\"btn btn-secondary display-4\">%s</a>\n";

static const char * html_division_end =
    "               </div>\n"
    "           </div>\n"
    "       </div>\n"
    "   </div>\n"
    "</div>\n";

static const char * html_division_box_end =
    "               </div>\n"
    "           </div>\n"
    "       </div>\n"
    "   </div>\n"
    "</div>\n";

static const char * html_footer =
    "</section>\n"
    "<section class=\"engine\"><a href=\"https://mobirise.info/p\">website templates free download</a>\n"
    "    </section><script src=\"assets/web/assets/jquery/jquery.min.js\"></script>\n"
    "<script src=\"assets/popper/popper.min.js\"></script>\n"
    "<script src=\"assets/tether/tether.min.js\"></script>\n"
    "<script src=\"assets/bootstrap/js/bootstrap.min.js\"></script>\n"
    "<script src=\"assets/smoothscroll/smooth-scroll.js\"></script>\n"
    "<script src=\"assets/theme/js/script.js\"></script>\n"
    "</body>\n"
    "</html>\n";

static const char * html_table_header =
    "<div class=\"table-wrapper\">\n"
    "   <div class=\"container scroll\">\n"
    "       <table class=\"table isSearch\"cellspacing=\"0\">\n"
    "           <thead>\n"
    "               <tr class=\"table-heads\">\n";

static const char * html_table_content =
    "   </tr>\n"
    "</thead>\n"
    "<tbody>\n";

static const char * html_table_start_entries =
    "               <tr>\n";

static const char * html_table_end_entries =
    "               </tr>\n";

static const char * html_table_entry = "<td class=\"body-item mbr-fonts-style display-7\">%s</td>";

static const char * html_table_entry_link = "<td class=\"body-item mbr-fonts-style display-7\"><a href=\"%s\" class=\"btn btn-secondary display-4\">%s</a></td>";

static const char * html_table_end =
    "           </tbody>\n"
    "       </table>\n"
    "   </div>\n"
    "</div>\n";

////////////////////////////////////////////////////////////////////

void html_generate_header( string_t * response, const char * page_name )
{
    string_t * temp = string_sprintf( html_header, page_name );
    string_append( response, temp );
    string_destroy( temp );
}

void html_generate_title( string_t * response, const char * page_title )
{
    string_t * temp = string_sprintf( html_section_title, page_title );
    string_append( response, temp );
    string_destroy( temp );
}

void html_generate_box_header( string_t * response )
{
    string_t * temp = string_create_ex( html_division_header );
    string_append( response, temp );
    string_destroy( temp );
}

void html_generate_box_header_title( string_t * response, const char * title )
{
    string_t * temp = string_sprintf( html_division_box_header, title );
    string_append( response, temp );
    string_destroy( temp );
}

void html_generate_box_title( string_t * response, const char * box_title )
{
    string_t * temp = string_sprintf( html_division_title, box_title );
    string_append( response, temp );
    string_destroy( temp );
}

void html_generate_box_extra_info( string_t * response, const char * info )
{
    string_t * temp = string_sprintf( html_division_extra_info, info );
    string_append( response, temp );
    string_destroy( temp );
}

void html_generate_box_temperature( string_t * response, float temperature )
{
    string_t * temp = string_sprintf( html_division_temperature, temperature );
    string_append( response, temp );
    string_destroy( temp );
}

void html_generate_box_image( string_t * response, const char * image_file )
{
    string_t * temp = string_sprintf( html_division_image, image_file );
    string_append( response, temp );
    string_destroy( temp );
}

void html_generate_button_header( string_t * response )
{
    string_t * temp = string_create_ex( html_button_header );
    string_append( response, temp );
    string_destroy( temp );
}

void html_generate_button( string_t * response, const char * link, const char * caption )
{
    string_t * temp = string_sprintf( html_section_button, link, caption );
    string_append( response, temp );
    string_destroy( temp );
}

void html_generate_box_end( string_t * response )
{
    string_t * temp = string_create_ex( html_division_end );
    string_append( response, temp );
    string_destroy( temp );
}

void html_generate_box_title_end( string_t * response )
{
    string_t * temp = string_create_ex( html_division_box_end );
    string_append( response, temp );
    string_destroy( temp );
}

void html_generate_footer( string_t * response )
{
    string_t * temp = string_create_ex( html_footer );
    string_append( response, temp );
    string_destroy( temp );
}

void html_generate_table_header( string_t * response )
{
    string_t * temp = string_create_ex( html_table_header );
    string_append( response, temp );
    string_destroy( temp );
}

void html_generate_table_content( string_t * response )
{
    string_t * temp = string_create_ex( html_table_content );
    string_append( response, temp );
    string_destroy( temp );
}

void html_generate_table_start_end( string_t * response, bool_t start )
{
    if( start == TRUE )
    {
        string_t * temp = string_create_ex( html_table_start_entries );
        string_append( response, temp );
        string_destroy( temp );
    }
    else
    {
        string_t * temp = string_create_ex( html_table_end_entries );
        string_append( response, temp );
        string_destroy( temp );
    }
}

void html_generate_table_entry( string_t * response, const char * caption, const char * link )
{
    if( link != NULL )
    {
        string_t * temp = string_sprintf( html_table_entry_link, link, caption );
        string_append( response, temp );
        string_destroy( temp );
    }
    else
    {
        string_t * temp = string_sprintf( html_table_entry, caption );
        string_append( response, temp );
        string_destroy( temp );
    }
}

void html_generate_table_end( string_t * response )
{
    string_t * temp = string_create_ex( html_table_end );
    string_append( response, temp );
    string_destroy( temp );
}
