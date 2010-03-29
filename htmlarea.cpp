/***************************************************************************
 *   Copyright (C) 2010 by Mirko Lindner   *
 *   mirko@sharism.cc   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

// #include <iostream>
#include <QtGui>
#include <QMessageBox>
#include <QTextBrowser>
#include <string>
#include <sstream>
// #include <vector>
#include "qmain.h"
#include <zim/file.h>
#include <zim/search.h>
#include <zim/fileimpl.h>

#include <cxxtools/log.h>

log_define("qvido.htmlarea");

///////////////////////////////////////////
// Functions related to htmlarea
void HtmlArea::linking( const QUrl &txt ){
	QString str = txt.toString(); 
	
// // 	check if url is an internal anchor if yes jump if not end request and query zimlib
	if (str.startsWith("#") == 1){
		this->scrollToAnchor(str);
	}else{
		this->setSource(this->source());
		this->setNewContent(1, str);
	}
}

void HtmlArea::setNewContent( int method, QString str = "" ){
	zim::Article article;
	
	if (method == 0){
		article = this->getRandomArticle();
	}else if( method == 1){
		article = this->getArticleFromUrl(str);
	}else if( method == 2){
		// first search
		zim::Search::Results result = this->searchArticleFromTitle(str);
		// if result = 1 display article
		if (result.size() == 1){
			//create ZIM file accessor
			zim::File file = this->get_file();
			article = file.getArticle(result[0].getArticle().getIndex());
		}
		// if result > 1 display options return at end
		else if (result.size() > 1){
			QString res;
			for (unsigned i = 0; i < result.size(); ++i)
        {
          res.append("<li><a href='" + QString::fromStdString(result[i].getArticle().getUrl()) + "'>" + QString::fromStdString(result[i].getArticle().getTitle()) + "</a></li>");
        }
			this->setText(res);
			return;
		}

	}
	
	//check if article is valid, if display if not show error
	if (article.good()){
		//TODO build history, set Title
		this->setText(QString::fromStdString(article.getPage()));
	}else{
		//construct error text
		QString errText = "The article you requested (";
		errText.append(str);
		errText.append(") could not be found.");
		
		//construct and display error box
		QMessageBox::information(qobject_cast<QMain *>(this->parentWidget()), "Error",
														 errText,
														 QMessageBox::Close);
	}
	
}

// // slots 
// // TODO ...is there any way to connect setNewContent to Actions directly using default values?
void HtmlArea::getRandom(){
	log_debug("getRandom called");
	this->setNewContent( 0 );
}

void HtmlArea::searchArticle(QString term){
	log_debug("searchArticle called");
	this->setNewContent( 2 , term);
}

//
////////////////////////////////////////////
////////////////////////////////////////////
// Zimlib functions

const zim::File& HtmlArea::get_file()
{
  static zim::File zimFile;

  if (!zimFile.good())
  {
    zimFile = zim::File(qobject_cast<QMain *>(this->parentWidget())->fileLocation);
    log_debug("number of articles: " << zimFile.getCountArticles());
  }

  return zimFile;
}

//get random article
//TODO get new article if article returned is current article
zim::Article HtmlArea::getRandomArticle(){
		
		//get file
		zim::File file = this->get_file();
		
		//create empty article
		zim::Article article;
		
//     do
// 		{
				// generate random number
				unsigned int seed = static_cast<unsigned int>(time(0));
				zim::size_type idx = static_cast<zim::size_type>(static_cast<double>(file.getCountArticles()) * rand_r(&seed) / RAND_MAX);
				
				//retrieve article
				article = file.getArticle(idx);
				
				//loop in case article is redirect
				do 
				{
						article = article.getRedirectArticle();
				}while(article.isRedirect());
    
// 		}while(article.getUrl() == current_url);

		return article;
}

zim::Article HtmlArea::getArticleFromUrl(QString url)
{
    // TODO unescape url

		//create ZIM file accessor
    zim::File file = this->get_file();
		
		//create empty article
		zim::Article article;
		
		// remove '+' signs
    QString term = url.replace( '+', ' ');

		//set default namespace
    char ns = 'A';

		//check for different namespace
    if (term.contains("/"))
    {
				int index = term.indexOf("/");
        if ( index == 1)
        {
            ns = term[0].toLatin1();
            term.remove(0, 2);
        }
 				//TODO what was this for?
				/*
        else
        {
            term.erase(1);
            ns = term[0];
            found2 = term.find("/");
            term.erase(0, term.indexOf("/"));
        }*/
    }
		
// // //     try to retrieve article
    try
    {
			article = file.getArticle(ns, term.toStdString());
			return article;
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
}

zim::Search::Results HtmlArea::searchArticleFromTitle(QString phrase)
{
		char ns;
    ns = 'A';
    
		zim::File file = get_file();
    
		zim::Article article;
		
    zim::Search::Results result;
    zim::Search search(file);
    search.setSearchLimit(25);
    search.find(result, ns, phrase.toStdString());
		
		return result;
}

// zim::Article HtmlArea::getArticleFromTitle(QString *phrase)
// {
// // 		historyCall = false;
// //     screenblock(1);
// 		
//     if( result.size() == 0)
//     {
// //         show_message("Error", "The article you requested (" + term + ")  was not found.");
// // 				screenblock(0);
// 				return article;
//     }else{ 
//       
//       if (result.size() == 1){
//         log_debug("one article in result");
//         
//         article = z.getArticle(result[0].getArticle().getIndex());
//         
//         //loop in case article is redirect
//         do 
//         {
//             article = article.getRedirectArticle();
//         }while(article.isRedirect());
//         
// 				return article;
//       }
//       else
//       {
//         log_debug("more than one article in result");
//         for (unsigned i = 0; i < result.size(); ++i)
//         {
//           res += "<li><a href='" + result[i].getArticle().getUrl() + "'>" + result[i].getArticle().getUrl() + "</a></li>";
//         }
// 				
//     
//       }
//       
// //       fill_gtkhtml(res, url, title);
//     }
// }
