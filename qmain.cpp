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

#include <QtGui>
#include <QWidget>
#include <QMessageBox>
#include "qmain.h"

QMain::QMain(std::string File)
{
		
		this->resize(320, 240);
		
		fileLocation = File;
		
		centralWidget = new HtmlArea(this);
    setCentralWidget(centralWidget);
		
		centralWidget->getRandom();
		registerCommands();
		QObject::connect(centralWidget,SIGNAL(anchorClicked(const QUrl &)),
										 centralWidget,SLOT(linking(const QUrl&)));
		QObject::connect(centralWidget,SIGNAL(sourceChanged(const QUrl &)),
										 centralWidget,SLOT(sourceChange(const QUrl&)));
										 
}

QMain::~QMain(){}

void QMain::searchDialog(){
		bool ok;
		QString text = QInputDialog::getText(this, tr("Search Article"),
                                          tr("Article Title"), QLineEdit::Normal,
                                          "", &ok);
		if (ok && !text.isEmpty())
			this->centralWidget->searchArticle(text);
			
}

void QMain::registerCommands()
{
		//get random article
		randomArticleAct = new QAction(tr("Load &Random Article"), this);
		randomArticleAct->setShortcut(tr("Ctrl+R"));
		randomArticleAct->setStatusTip(tr("Random Article"));
		connect(randomArticleAct, SIGNAL(triggered()), this->centralWidget, SLOT(getRandom()));	
		this->addAction(randomArticleAct);

		//get search dialog
		searchArticleAct = new QAction(tr("&Search Dialog"), this);
		searchArticleAct->setShortcut(tr("Ctrl+S"));
		searchArticleAct->setStatusTip(tr("Search for Article"));
		connect(searchArticleAct, SIGNAL(triggered()), this, SLOT(searchDialog()));	
		this->addAction(searchArticleAct);

		//display help
		displayHelpAct = new QAction(tr("Display &H"), this);
		displayHelpAct->setShortcut(tr("F1"));
		displayHelpAct->setStatusTip(tr("Display Help"));
		connect(displayHelpAct, SIGNAL(triggered()), this, SLOT(displayHelp()));	
		this->addAction(displayHelpAct);
}

void QMain::displayHelp(){
	QString txt = "Usage: \n";
	txt.append("Ctrl + R = Display random article\n");
	txt.append("Ctrl + S = Search for article\n");
	txt.append("Ctrl + T = Go to articles top\n");
	txt.append("Tab = Rotate through links\n");
	txt.append("Enter = Activate link\n");
	txt.append("Ctrl + H = Display history\n");
	txt.append("Ctrl + B = Go back in history\n");
	txt.append("Ctrl + F = Go forward in history\n");
	txt.append("Ctrl + Q = Quit Vido\n");
	txt.append("F1 = Display this help\n");

	QMessageBox::information(this, "Help",
													 txt,
                           QMessageBox::Close);
 
}