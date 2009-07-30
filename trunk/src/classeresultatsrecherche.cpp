/*
	� Murielle Descerisiers, 2009
	murielle.descerisiers@gmail.com

	Ce logiciel est un programme informatique d�velopp� au Qu�bec et servant �
	consulter le dictionnaire de la langue fran�aise d'�mile Littr�.

	Ce logiciel est r�gi par la licence CeCILL soumise au droit fran�ais et respectant
	les principes de diffusion des logiciels libres. Vous pouvez utiliser, modifier et/ou
	redistribuer ce programme sous les conditions de la licence CeCILL telle que diffus�e
	par le CEA, le CNRS et l'INRIA sur le site http://www.cecill.info.

	En contrepartie de l'accessibilit� au code source et des droits de copie, de
	modification et de redistribution accord�s par cette licence, il n'est offert aux
	utilisateurs qu'une garantie limit�e. Pour les m�mes raisons, seule une
	responsabilit� restreinte p�se sur l'auteur du programme, le titulaire des droits
	patrimoniaux et les conc�dants successifs.

	� cet �gard l'attention de l'utilisateur est attir�e sur les risques associ�s au
	chargement, � l'utilisation, � la modification et/ou au d�veloppement et � la
	reproduction du logiciel par l'utilisateur �tant donn� sa sp�cificit� de logiciel
	libre, qui peut le rendre complexe � manipuler et qui le r�serve donc � des
	d�veloppeurs et des professionnels avertis poss�dant des connaissances informatiques
	approfondies. Les utilisateurs sont donc invit�s � charger et tester l'ad�quation du
	logiciel � leurs besoins dans des conditions permettant d'assurer la s�curit� de
	leurs syst�mes et ou de leurs donn�es et, plus g�n�ralement, � l'utiliser et
	l'exploiter dans les m�mes conditions de s�curit�.

	Le fait que vous puissiez acc�der � cet en-t�te signifie que vous avez pris
	connaissance de la licence CeCILL, et que vous en avez accept� les termes.
*/

#include "classeresultatsrecherche.h"

classeResultatsRecherche::classeResultatsRecherche(QObject *parent,
		QHash<int, structureEntree> *table) : QStyledItemDelegate(parent),
		tableEntrees(table), police("DejaVu Serif", 10)
{
}

QSize classeResultatsRecherche::sizeHint(const QStyleOptionViewItem &option,
		const QModelIndex &index) const
{
	QSize taille(QStyledItemDelegate::sizeHint(option, index));
	taille.setHeight(nombreHauteurEntree);
	return taille;
}

void classeResultatsRecherche::paint(QPainter *painter, const QStyleOptionViewItem &option,
		const QModelIndex &index) const
{
	QRect rectangleTitre(option.rect);
	rectangleTitre.setHeight(nombreHauteurTitre);

	QLinearGradient degrade(rectangleTitre.topLeft(), rectangleTitre.bottomLeft());
	degrade.setColorAt(0.0, QColor::fromRgb((option.state & QStyle::State_Selected)
			? 0x7777f6 : 0x777777));
	degrade.setColorAt(0.4, QColor::fromRgb((option.state & QStyle::State_Selected)
			? 0x6060e3 : 0x606060));
	degrade.setColorAt(0.401, QColor::fromRgb((option.state & QStyle::State_Selected)
			? 0x5757da : 0x575757));
	degrade.setColorAt(1.0, QColor::fromRgb((option.state & QStyle::State_Selected)
			? 0x333394 : 0x333333));

	const int indexEntree(index.data(Qt::UserRole).toInt());
	if(indexEntree != -1) {
		painter->fillRect(rectangleTitre, QBrush(degrade));
		painter->setPen(Qt::white);
		painter->setFont(police);
		painter->drawText(rectangleTitre, Qt::AlignCenter,
				tableEntrees->value(indexEntree).texteEntree);
	}

	QTextDocument document;
	document.setUndoRedoEnabled(false);
	document.setDefaultFont(police);
	document.setTextWidth(option.rect.width());
	document.setHtml(index.data().toString());
	painter->save();
	painter->translate(rectangleTitre.bottomLeft());
	document.drawContents(painter, QRect(0, 0, option.rect.width(),
			option.rect.height() - nombreHauteurTitre));
	painter->restore();
}
