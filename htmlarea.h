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

#include <QTextBrowser>
#include <QWidget>
#include <zim/file.h>
#include <zim/search.h>

class UserEventFilter : public QObject
{
		Q_OBJECT

	public:
		UserEventFilter() : QObject() {}

	protected:
		bool eventFilter(QObject *obj, QEvent *event);
};

class HtmlArea : public QTextBrowser
{
	Q_OBJECT

	public:
		HtmlArea(QWidget * parent = 0) : QTextBrowser(parent) {}
		void searchArticle(QString term);

	private:
		QString url;
		QObject filter;
		zim::Article getArticleFromUrl(QString url);
		zim::Search::Results searchArticleFromTitle(QString phrase);
		zim::Article getRandomArticle();
		const zim::File& get_file();
		void setNewContent( int method, QString str );
		QVariant loadResource(int type, const QUrl &name);
		
	public Q_SLOTS:
		void linking( const QUrl &txt );
		void sourceChange( const QUrl &txt );
		void getRandom();
};
