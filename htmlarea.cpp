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

bool UserEventFilter::eventFilter(QObject *obj, QEvent *event)
{
		if (event->type() == QEvent::KeyPress) {
				QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
				log_debug("Ate key press " << keyEvent->key());
				return true;
		} else {
				// standard event processing
				return QObject::eventFilter(obj, event);
		}
}

///////////////////////////////////////////
// Functions related to htmlarea
void HtmlArea::linking( const QUrl &txt ){
	QString str = txt.toString(); 
	
// // 	check if url is an internal anchor if yes jump if not end request and query zimlib
	if (str.startsWith("#") == 1){
		this->scrollToAnchor(str);
	}else{
		log_debug(str.toUtf8().data());
		this->setSource(this->source());
		this->setNewContent(1, str);
	}
}

void HtmlArea::setNewContent( int method, QString str = "" ){
	
	qobject_cast<QMain *>(this->parentWidget())->setEnabled(false);
	QString current = this->toHtml();
	this->setText("<html><body><br/><br/><br/><br/><p>Loading ... </p></body></html>");
	qApp->processEvents();
	
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
			log_debug("result size 1");
			//create ZIM file accessor
			zim::File file = this->get_file();
			article = file.getArticle(result[0].getArticle().getIndex());
		}
		// if result > 1 display options return at end
		else if (result.size() > 1){
			log_debug("more than one result");
			QString res;
			for (unsigned i = 0; i < result.size(); ++i)
        {
          res.append("<li><a href='" + QString::fromUtf8(result[i].getArticle().getUrl().c_str()) + "'>" + QString::fromUtf8(result[i].getArticle().getTitle().c_str()) + "</a></li>");
        }
			this->setText(res);
			qApp->processEvents();
			qobject_cast<QMain *>(this->parentWidget())->setEnabled(true);
			return;
		}

	}
	
	//check if article is valid, if display if not show error
	if (article.good()){
		log_debug("article is good");
		this->url = QString::fromUtf8(article.getUrl().c_str());
		log_debug("Url set");
		//TODO build history, set Title
		//TODO certain zimfiles break here
		// example full german file breaks here with article "Trockenrasierer"
		std::string content = article.getPage();
		this->setText(QString::fromUtf8(content.c_str()));
		
		log_debug("Text set");
// 		log_debug("index: " << article.getIndex());
// 		log_debug("enabled: " << this->isEnabled());
		log_debug("string: " << str.toUtf8().data());
		qApp->processEvents();
		qobject_cast<QMain *>(this->parentWidget())->setEnabled(true);
		
	}else{
		this->setText(current);
		//construct error text
		QString errText = "The article you requested (";
		errText.append(str);
		errText.append(") could not be found.");
		log_debug("string: " << str.toUtf8().data());
		qApp->processEvents();
		qobject_cast<QMain *>(this->parentWidget())->setEnabled(true);
		
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
	if(this->isEnabled()){
		this->setNewContent( 0 );
	}
}

void HtmlArea::searchArticle(QString term){
	log_debug("searchArticle called");
	if(this->isEnabled()){
		this->setNewContent( 2 , term);
	}
}

//
////////////////////////////////////////////
////////////////////////////////////////////
// Debug functions
void HtmlArea::sourceChange( const QUrl &txt ){
	QString str = txt.toString();
	log_debug("source: " << str.toStdString());
}


//
////////////////////////////////////////////

//reimplimentations
QVariant HtmlArea::loadResource(int type, const QUrl &name)
{

		QVariant qv;
		
		// check if requested resource is an image
		if (type == 2){
			zim::Article article;
			article = getArticleFromUrl(name.toString());
			
			if(article.good()){
				QString mtype(article.getMimeType().c_str());
				
				QByteArray data = QByteArray::fromRawData(article.getData().data(), article.getData().size());

				QImage img;
				
				mtype.remove("image/");
				img.loadFromData(data, mtype.toUpper().toLatin1());
				
// 				log_debug("index: " << article.getIndex() << " height: " << article.getData().size() << " mtype: " << std::string(mtype.toUpper().toLatin1()));
				qv = img;

			}
		}
		
		return qv;
}


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
zim::Article HtmlArea::getRandomArticle(){
		
		//get file
		zim::File file = this->get_file();
		
		//create empty article
		zim::Article article;
// 		log_debug("before random loop");
    do
		{
				// generate random number
				unsigned int seed = static_cast<unsigned int>(time(0));
				zim::size_type idx = static_cast<zim::size_type>(static_cast<double>(file.getCountArticles()) * rand_r(&seed) / RAND_MAX);
				
				//retrieve article
				article = file.getArticle(idx);
// 				article = file.getArticle(151);
				log_debug("idx: " << idx);
				//loop in case article is redirect
// 				log_debug("before redirect loop");
				do 
				{
						article = article.getRedirectArticle();
						log_debug("random url: " << article.getUrl());
				}while(article.isRedirect());
    
		}while(article.getUrl() == this->url.toStdString());
		
// 		log_debug("after random loop");
		
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
				if(term.startsWith("/")){
					term.remove(0,1);
				}
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
			article = file.getArticle(ns, term.toUtf8().data());
// 			QString mtype(article.getMimeType().c_str());
// 			if(mtype.contains("image/") == false){
// 				log_debug("term :" << term.toStdString());
// 			}
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
		char *terms = phrase.toUtf8().data();
		
    search.find(result, ns, terms);
		log_debug("term :" << phrase.toUtf8().data());
		return result;
}
