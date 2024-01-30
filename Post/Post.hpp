/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Post.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onaciri <onaciri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 09:09:48 by onaciri           #+#    #+#             */
/*   Updated: 2024/01/28 10:08:22 by onaciri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef POST_HPP
#define POST_HPP

#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <map>
#include <vector>
#include <fstream>
#include <bits/stdc++.h> 
#include "../elidrys/src/Method.hpp"
#include <iostream>
#include <ctime>
#include <sstream>

class Post : public Method
{
    private:
        /*function*/
		void mimeType();
    private:
        /* data */
		int crfile;
		int MethodType;
        int special;
        int rare;
        size_t left_over;
        int chunk_ctl;
		size_t size_len;
        size_t total_Body;
        size_t chunk_left;
        std::string buffer;
        std::string buff_chunk;
		std::map<std::string, std::string> mime;
		std::fstream outFile;
        std::fstream out;
        std::string sep;
        std::string sep_end;
        std::string sep_found;
        int find_sep;
    public:
        Post();
        Post(const Post& post);
        Post& operator=(const Post& post);
        ~Post();
        
        int process(std::string body, size_t body_size, int event);
		void openFile(std::string body, size_t body_size);
		void normalFile(std::string body, size_t body_size);
        
        void chunked_file(std::string body, size_t body_size);
        void chunk_write(std::string body, size_t body_size);

        void    ft_boundary(std::string& body);

};


#endif