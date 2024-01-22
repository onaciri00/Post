#include "Post.hpp"

Post::Post()
{
	crfile = 0;
    chunk_ctl = 0;
    total_Body = 0;
    size_len = 0;
    left_over = 0;
    chunk_left = 0;
    rare = 0;
    special = 0;
    mimeType();
}

Post::Post(const Post& post)
{
    *this = post;
}

Post& Post::operator=(const Post& post)
{
    (void)post;
    return *this;
}

Post::~Post()
{

}


/*work*/

void Post::mimeType()
{
   std::string str =
    "  text/html html\n"
    "text/css   css\n"
    "text/xml  xml\n"
    "image/gif gif\n"
    "image/jpeg jpeg\n"
    "application/javascript   js\n"
    "application/atom+xml  atom\n"
    "application/rss+xml  rss\n"
    "text/mathml    mml\n"
    "text/plain txt\n"
    "text/vnd.sun.j2me.app-descriptor    jad\n"
    "text/vnd.wap.wml  wml\n"
    "text/x-component htc\n"
    "image/avif avif\n"
    "image/png  png\n"
    "image/svg+xml  svg\n"
    "image/tiff  tiff\n"
    "image/vnd.wap.wbmp wbmp\n"
    "image/webp webp\n"
    "image/x-icon ico\n"
    "image/x-jng  jng\n"
    "image/x-ms-bmp  bmp\n"
    "font/woff   woff\n"
    "font/woff2  woff2\n"
    "application/java-archive jar\n"
    "application/json json\n"
    "application/mac-binhex40  hqx\n"
    "application/msword   doc\n"
    "application/pdf   pdf\n"
    "application/postscript                           ps\n"
    "application/rtf                                  rtf\n"
    "application/vnd.apple.mpegurl                    m3u8\n"
    "application/vnd.google-earth.kml+xml             kml\n"
    "application/vnd.google-earth.kmz                 kmz\n"
    "application/vnd.ms-excel                         xls\n"
    "application/vnd.ms-fontobject                    eot\n"
    "application/vnd.ms-powerpoint                    ppt\n"
    "application/vnd.oasis.opendocument.graphics      odg\n"
    "application/vnd.oasis.opendocument.presentation  odp\n"
    "application/vnd.oasis.opendocument.spreadsheet   ods\n"
    "application/vnd.oasis.opendocument.text          odt\n"
    "application/vnd.openxmlformats-officedocument.presentationml.presentation pptx\n"
    "application/vnd.openxmlformats-officedocument.spreadsheetml.sheet xlsx\n"
    "application/vnd.openxmlformats-officedocument.wordprocessingml.document docx\n"
    "application/vnd.wap.wmlc  wmlc\n"
    "application/wasm   wasm\n"
    "application/x-7z-compressed  7z\n"
    "application/x-cocoa cco\n"
    "application/x-java-archive-diff  jardiff\n"
    "application/x-java-jnlp-file jnlp\n"
    "application/x-makeself   run\n"
    "application/x-perl   pl\n"
    "application/x-pilot  pdb\n"
    "application/x-rar-compressed  rar\n"
    "application/x-redhat-package-manager    rpm\n"
    "application/x-sea     sea\n"
    "application/x-shockwave-flash     swf\n"
    "application/x-stuffit  sit\n"
    "application/x-tcl    tcl\n"
    "application/x-x509-ca-cert   crt\n"
    "application/x-xpinstall                          xpi\n"
    "application/xhtml+xml                            xhtml\n"
    "application/xspf+xml                             xspf\n"
    "application/zip                                  zip\n"
    "application/octet-stream bin\n"
    "audio/midi  midi\n"
    "audio/mpeg mp3\n"
    "audio/ogg ogg\n"
    "audio/x-m4a       m4a\n"
    "audio/x-realaudio    ra\n"
    "video/3gpp  3gpp\n"
    "video/mp2t   ts\n"
    "video/mp4    mp4\n"
    "video/mpeg   mpeg\n"
    "video/quicktime   mov\n"
    "video/webm   webm\n"
    "video/x-flv  flv\n"
    "video/x-m4v  m4v\n"
    "video/x-mng  mng\n"
    "video/x-ms-asf     asf\n"
    "video/x-ms-wmv    wmv\n"
    "video/x-msvideo   avi";
    std::istringstream input(str);
    std::string line;
    str.clear();
    while (input >> line >> str)
        mime[line] = str;
    
}

void Post::openFile(std::string body, size_t body_size)
{
	std::string mimeVal;
	if (headers.find("Transfer-Encoding") != headers.end())
    {
        if ((headers.find("Transfer-Encoding"))->second == "chunked")
		{
            std::cout << "HERE \n";
			MethodType = 1;
		}
		else
		{
			MethodType = 2;
		}
    }
	if (headers.find("Content-Type") != headers.end())
    {
        if (mime.find( headers.find("Content-Type")->second) != mime.end())
		{
			mimeVal = mime.find((headers.find("Content-Type")->second))->second;
		}
		else
		{
			mimeVal = "x";
		}
    }
    else
    {
        std::cout << "No Content Type\n";
		crfile = -2;
        return ;
    }
	// Get the current time
    std::time_t currentTime = std::time(NULL);
    // Convert time to struct tm in local time
    std::tm* timeInfo = std::localtime(&currentTime);
    // Format the time into a string
    char time_B[80];  // Sufficiently large time_B
    std::strftime(time_B, sizeof(time_B), "%Y-%m-%d_%H-%M-%S", timeInfo);
    // Get the resulting string
    std::string currentTimeString = time_B;
	std::string fileName = time_B;
	std::string dot  = ".";
	fileName = time_B + dot;
	fileName = fileName + mimeVal;
	outFile.open(fileName.c_str(), std::ios::out | std::ios::binary);
    if (headers.find("Content-Length") != headers.end())
    {
        size_len =  (size_t)std::atoi((headers.find("Content-Length")->second).c_str());
    }
	if (outFile.is_open())
	{
        crfile = 1;
        body_size =  body.size(); 
        chunked_file(body, body_size);
        
    }
    else
    {
        crfile = -1;
    }
    
}

void Post::normalFile(std::string body, size_t body_size)
{
	outFile.write(body.c_str(), body.size());
    if (body_size >= size_len)
    {
        outFile.close();
        crfile = -2;
    }
}


void Post::chunk_write(std::string body, size_t body_size)
{
    if (chunk_ctl >= (int)body.size())
    {
        std::cout << "Metod 1\n";
        std::cout << "body: "<< body.size()<< "   "<<body_size<<std::endl;
        outFile.write(body.c_str(), body.size());
        std::cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";
        // std::cout << body << std::endl;
        // std::cout << chunk_ctl<<std::endl;
        std::streampos position = outFile.tellp();
        if (outFile.good()) {
            std::cout << "Write operation successful." << std::endl;
            std::cout << "Bytes written: " << position << " bytes." << std::endl;
        } 
        else {
            std::cerr << "Error occurred during write operation." << std::endl;
        }

        std::cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";

        std::cout << "out Metod 1\n";
        if ((int) chunk_ctl - body.size() < 0)
        {
            std::cout << "lol1";
            exit(1);
        }
        std::cout << "after sub   " << chunk_ctl<<std::endl;
        buffer = "";
        left_over = 0;
        if ((int)body.size() == chunk_ctl)
        {
             rare = 1;
             chunk_ctl = 0;
             return;
        }
        chunk_ctl = chunk_ctl - body.size();
    }
    else
    {
        std::string tmp = "";
        std::string chunks_s;
        std::stringstream ss;

        std::cout << "Method 2\n";
        buffer = "";
        tmp.append(body, 0, chunk_ctl);
        if (body.size() - chunk_ctl == 1)
        {
            outFile.write(tmp.c_str(), tmp.size());

            // chunk_ctl = chunk_ctl - tmp.size();
            buff_chunk = body.substr(chunk_ctl, 1);
            left_over = 1;
            chunk_ctl = 0;
            rare = 1;
            return ;
        }
        buffer = body.substr(chunk_ctl + 2, body.size() - chunk_ctl - 2);
        if (buffer.find("\r\n") != std::string::npos)
        {
            chunks_s = buffer.substr(0, buffer.find("\r\n"));
            buffer = buffer.substr(buffer.find("\r\n") + 2, buffer.size() -  buffer.find("\r\n") - 2);
            ss << chunks_s;
            ss >> std::hex >> chunk_ctl;
            std::cout << "chunks " <<chunk_ctl  << "chunks body = "<< chunks_s<<std::endl;
            if (!chunk_ctl)
            {
                outFile.write(tmp.c_str(), tmp.size());
                outFile.close();
                crfile = -2;
                std::cout <<"chunk3 -== " << chunk_ctl << std::endl;
                std::cout << "Ima\n";
                exit(1) ;
            }
            if (chunk_ctl < (int)tmp.size())
            {
                std::cout << "special 1\n";
                exit(1);
            }
            tmp.append(buffer, 0, buffer.size());
            if (chunk_ctl < (int)tmp.size())
            {
                std::cout << "special 1\n";
                exit(1);
            }
            outFile.write(tmp.c_str(), tmp.size());
            chunk_ctl = chunk_ctl - buffer.size();
        }
        else
        {
            outFile.write(tmp.c_str(), tmp.size());
            // chunk_ctl = chunk_ctl - tmp.size();
            buff_chunk = buffer;
            left_over = buffer.size();
            chunk_ctl = 0;
        }

    }

}

void Post::chunked_file(std::string body, size_t body_size)
{
    std::cout << "IN CHUNKED"<<std::endl;
    std::stringstream ss;
    if (left_over)
    {
        buffer = "";
        std::cout << "size of buff " << left_over << "size of body " << body.size()<<std::endl;
        std::cout << "*********************************************************************some buff*******************\n"<<(int)buff_chunk[0]<<std::endl;
        buffer.append(buff_chunk, 0, left_over);
        std::cout << "*********************************************************************some buff1*******************\n"<<(int)buffer[0]<<std::endl;
        std::cout <<"buffer\n"<< buffer << "\n bufferchunk\n" << buff_chunk<<std::endl;
        buffer.append(body, 0, body.size());
        std::cout <<"buffer\n"<< buffer << "\n body\n" << body<<std::endl;
        body = buffer;
        body_size = left_over + body.size();
        left_over = 0;
        // exit(1);
    }
    if (chunk_ctl)
    {
        std::cout << "there is chunk lef prev\n";
        chunk_write(body, body_size);
        std::cout << "chunks is now " << chunk_ctl << std::endl;
    }
    else
    {

        std::cout << "chunks is zero\n";
        std::string chunks_s;
        if (rare)
        {
            body = body.substr(2, body.size() - 2);
            rare = 0;
        }
        std::cout << "finallllllllllllllllllllllllllllllllll bosd\n"<<body;
        if (body.find("\r\n") == std::string::npos)
        {
            std::cout << "not found \n";
            exit(1);
        }
        chunks_s = body.substr(0, body.find("\r\n"));
        body = body.substr(body.find("\r\n") + 2, body.size() -  body.find("\r\n") - 2);
        ss << chunks_s;
        ss >> std::hex >> chunk_ctl;
        std::cout << "chunks " <<chunk_ctl  << "chunks body = "<< chunks_s<<std::endl;
		if (!chunk_ctl)
		{
           	outFile.close();
           	crfile = -2;
            std::cout <<"chunk3 -== " << chunk_ctl << std::endl;
            std::cout << "Ima\n";
            exit(1) ;
		}
        body_size = body_size - chunks_s.size() - 2;
        std::cout << "CHUNKS = " << chunk_ctl << "Body_size "<< body_size << "dec = "<<chunks_s.size() + 2 <<std::endl;
        chunk_write(body, body_size);
    }
}

void Post::process(std::string body, size_t body_size)
{
    std::cout <<"HERRRRRRRRRRRR IS body as al  " <<body_size<<std::endl;
    std::cout << "GO   "<< crfile << std::endl;
    std::cout << "*********************************\n";
    std::cout << "-----------     " << chunk_ctl << "   -----------------------*\n";
    std::cout << "*********************************\n";
    std::cout << "ddsds\n";
    std::cout << body <<std::endl;
    std::cout << "\n some => "<<(int)body[0]<<std::endl;
    if (body_size == 2)
    {
        buff_chunk = body;
        left_over = 2;
        return ;
    } 
    if (crfile == -2)
        return ;
	 if (crfile > 0)
        chunked_file(body, body_size);//remove
    // {
    //     if (MethodType == 2)
	// 	    normalFile(body, body_size);
    //   else if (MethodType == 1)
    //        chunked_file(body);
        
    // }
	else if (!crfile)
		openFile(body, body_size);
}



