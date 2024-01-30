/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Post.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onaciri <onaciri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 10:40:02 by onaciri           #+#    #+#             */
/*   Updated: 2024/01/30 15:08:09 by onaciri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
    end = 0;
    MethodType = 0;
    find_sep = 0;
    sep = "";
	sep_found = "";
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
			MethodType = 1;
		}
    }
    if (headers.find("Content-Type") != headers.end())
    {
        std::string tmp_C = (headers.find("Content-Type"))->second;
		if (tmp_C.find("boundary=") != std::string::npos)
		{
			buffer = tmp_C.substr(tmp_C.find("boundary=") + strlen("boundary=") , tmp_C.size() - tmp_C.find("boundary=") - strlen("boundary="));
			MethodType = 3;
			sep = "--";
			sep.append(buffer,0, buffer.size());
            sep_end = sep + "--";
			std::cout << "go~"<<sep<<std::endl;
            std::cout << "go~"<<sep_end<<std::endl;
			buffer = "";
		}
		crfile = 1;
		ft_boundary(body);
		return ;
    }
    if (!MethodType)
    {
        MethodType = 2;

    }
	if (MethodType != 3 && headers.find("Content-Type") != headers.end())
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
    else if (MethodType != 3)
    {
        std::cout << "No Content Type\n";
		crfile = -2;
        end = 1;
        return ;
    }
	if (MethodType != 3)
	{
		
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
	}
    if (headers.find("Content-Length") != headers.end())
    {
        size_len =  (size_t)std::atoi((headers.find("Content-Length")->second).c_str());
    }
    else
    {
        end = 1;
        return ;
    }
	if (MethodType != 3 && outFile.is_open())
	{
        crfile = 1;
        body_size =  body.size();
        // if (MethodType == 2)
        //     normalFile(body, body_size);
        // else
        //     chunked_file(body, body_size);        
    }
    else
    {
		if (MethodType != 3)
		{
        	crfile = -1;
        	end = 1;
		}
		else
		{
			crfile = 1;
			ft_boundary(body);
		}
    }
    
}

void Post::normalFile(std::string body, size_t body_size)
{
    (void)body_size;
	outFile.write(body.c_str(), body.size());
    total_Body += body.size();
    if (total_Body >= size_len)
    {
        out.close();
        outFile.close();
        crfile = -2;
        end = 1;
    }
}


void Post::chunk_write(std::string body, size_t body_size)
{
    if (chunk_ctl >= (int)body.size())
    {
        (void)body_size;
        outFile.write(body.c_str(), body.size());

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

        buffer = "";
        tmp.append(body, 0, chunk_ctl);
        if (body.size() - chunk_ctl == 1)
        {
            outFile.write(tmp.c_str(), tmp.size());

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
            if (!chunk_ctl)
            {
                outFile.write(tmp.c_str(), tmp.size());
                outFile.close();
                crfile = -2;
                end = 1;
                            out.close();

                return ;
            }
            tmp.append(buffer, 0, buffer.size());
            outFile.write(tmp.c_str(), tmp.size());
            chunk_ctl = chunk_ctl - buffer.size();
        }
        else
        {
            outFile.write(tmp.c_str(), tmp.size());
            buff_chunk = buffer;
            left_over = buffer.size();
            chunk_ctl = 0;
        }

    }

}

void Post::chunked_file(std::string body, size_t body_size)
{
    std::stringstream ss;
    if (left_over)
    {
        buffer = "";
        buffer.append(buff_chunk, 0, left_over);
        buffer.append(body, 0, body.size());
        body = buffer;
        body_size = left_over + body.size();
        left_over = 0;
    }
    if (chunk_ctl)
    {
        chunk_write(body, body_size);
    }
    else
    {

        std::string chunks_s;
        if (rare)
        {
            body = body.substr(2, body.size() - 2);
            rare = 0;
        }
        if (body.find("\r\n") == std::string::npos)
        {
            std::cout << "not found \n";
            end = 1;
        }
        chunks_s = body.substr(0, body.find("\r\n"));
        body = body.substr(body.find("\r\n") + 2, body.size() -  body.find("\r\n") - 2);
        ss << chunks_s;
        ss >> std::hex >> chunk_ctl;
		if (!chunk_ctl)
		{
           	outFile.close();
           	crfile = -2;
            end = 1;
            out.close();
            return ;
		}
        body_size = body_size - chunks_s.size() - 2;
        chunk_write(body, body_size);
    }
}


void    Post::ft_boundary(std::string& body)
{
    size_t pos;
    size_t pos1;
	std::cout << "\n\n*************************************** HELLLOOOOOOOOOO *************************************\n\n";
	// std::cout << find_sep<<std::endl;
 	// std::cout << "Sep before -> "<< sep<<"."<<std::endl;//remove
    std::cout << "boyd BEFOR \n" << body<<std::endl;
    if (left_over)
    {
        std::cout << "buffer is \n" << buffer<<std::endl;
        
        buffer.append(body, 0, body.size());
        left_over = 0;
        body = buffer;
        buffer = "";
    }
    std::cout << "\n\n+-+-+-+-+-+-+-+Body is good ++++-+++-++-+++-++-\n\n" << body<<std::endl;
	if (body.find("\r") != std::string::npos && body.find("\r") + 3 - body.size() < sep.size())
	{
		//special case if \r arrive but without the complete size 
		std::cout << "IN CASE N~1\n\n";
		std::cout << "Body\n" << body << "\nsep size " << sep.size()<< "\npos-> " << body.find("\r")<<std::endl;
		buffer = body;
		left_over = body.size();
		return ;
	}
    if (body.find(sep_end) != std::string::npos)
    {
        std::cout << "\n******+++++"<<  sep_end<<std::endl;
		std::cout << "IN CASE N~2.3\n\n";
        std::cout << "Body is ="<< body<<"npos= " << body.find(sep_end) <<std::endl;
		pos = body.find(sep_end);
        if (!pos || pos == 2)
            return ;
		out.write(body.c_str(), pos - 2);
		out.close();
		end = 1;
        return ;
    }
	if (body.find(sep) != std::string::npos)
	{
        
		std::cout << "IN CASE N~2\n\n";
		std::cout << "Bodyis="<<body<<std::endl;
        if (body.find("\r\n\r\n") != std::string::npos)
		{
            pos = body.find(sep);
			sep_found = body.substr(pos, sep.size());
			if (sep != sep_found)
			{
                std::cout <<"sep here is->\n"<< sep <<"\nsep found is \n" << sep_found<<std::endl;
				std::cout << "4arib\n";
				exit(1);
			}
            if (out.is_open())
            {
                if (pos > 2)
                {
                    buffer = body.substr(0, pos - 2);
                    std::cout << "we got him \n"<< "the body writing\n "<< buffer<<std::endl;
                    out.write(buffer.c_str(), buffer.size());
                    buffer = body.substr(pos, body.size() - pos - 2);
                    std::cout <<  "buffer is now \n"<< buffer<<std::endl;
                    left_over = buffer.size();
                    out.close();
                    return ;
                }
            }
			std::cout << "Sep after ->\n"<< sep<<"."<<std::endl;//remove
			std::cout << "Sep end ->\n"<< sep_end <<"."<<std::endl;//remove
			std::cout << "Sep found ->\n"<< sep_found <<"."<<std::endl;//remove
			if (body.find("filename") != std::string::npos)
			{
				pos = body.find("filename");
                if (body.find("filename", pos + 1) != std::string::npos)
                    pos1 = body.find(";", pos);
                else
				    pos1 = body.find("\r\n", pos);
				std::cout << "befor pos=" << pos<<std::endl;
				std::cout << "befor pos1=" <<pos1 - 1<<std::endl;
				if (pos1 <= 1)
					pos1 = 2;
				std::string file = body.substr(pos + strlen("filename=") + 1, pos1 - ( strlen("filename=") + 1) - pos - 1);
				std::cout << "File Name is-"<<file <<"."<<std::endl;
				out.open(file.c_str(), std::ios::out | std::ios::binary);
				if (out.is_open())
					std::cout << "FILE opened\n";
				else
                {
                    std::cout << "File Problem\n";
					exit(4);
                    
                }
				
			}
			else
			{
				std::cout << "No File Name\n";
				//make Error page
				return ;
			}
			std::cout << "IN CASE N~2.1\n\n";
			buffer = "";
			pos = body.find("\r\n\r\n");
			buffer.append(body, pos + 4, body.size() - (pos + 4));
			body = buffer;
			std::cout << "Body for true\n" << body<<std::endl;
            out.write(body.c_str(), body.size() );
            buffer = "";
		}
		else
		{
			std::cout << "IN CASE N~3\n\n";
            buffer = body;
            left_over = body.size();
		}
	}
    else
    {
        std::cout << "Bodyis="<<body<<std::endl;
        if (out.is_open())
        {
            std::cout << "+++++++++++++++++++++++body \n\n\n------>\n" << body<<std::endl;
            out.write(body.c_str(), body.size() );
        }
    }
	
}

int Post::process(std::string body, size_t body_size, int event)
{
    
    // x
    std::cout << "\n\n>>>>Here>>>>>\n\n";
    (void)event;
    if (crfile == -2)
        return 1;
    if (body_size == 2 && MethodType == 1)
    {
        buff_chunk = body;
        left_over = 2;
        return 1;
    } 
	 if (crfile > 0)
        ft_boundary(body);
    // {
    //     if (MethodType == 2)
	// 	    normalFile(body, body_size);
    //   else if (MethodType == 1)
    //        chunked_file(body, body_size);
        
    // }
	else if (!crfile)
		openFile(body, body_size);
    std::cout << "Here1\n\n";
    return 1;
}
