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

#include "classesurligneurtypographie.h"

classeSurligneurTypographie::classeSurligneurTypographie(QTextDocument *parent) :
		QSyntaxHighlighter(parent)
{
}

void classeSurligneurTypographie::SurlignerMotsClefs(const QString &texte,
		const QStringList &listeMotsClefs, const QTextCharFormat &formatTexte)
{
	foreach(QString texteMotClef, listeMotsClefs) {
		texteMotClef = "\\b" + texteMotClef + "\\b";
		QRegExp expression(texteMotClef, Qt::CaseInsensitive);
		int nombreIndex(texte.indexOf(expression));
		while (nombreIndex >= 0) {
			const int nombreLongueur(expression.matchedLength());
			setFormat(nombreIndex, nombreLongueur, formatTexte);
			nombreIndex = texte.indexOf(expression, nombreIndex + nombreLongueur);
		}
	}
}

void classeSurligneurTypographie::highlightBlock(const QString &text)
{
	QTextCharFormat formatTexte;
	formatTexte.setFontWeight(QFont::Bold);

	QStringList listeMotsClefs;
	listeMotsClefs << "corps";
	listeMotsClefs << "prononciation";
	listeMotsClefs << QString::fromUtf8("r\303\251sum\303\251-num\303\251ro-sens");
	listeMotsClefs << QString::fromUtf8("num\303\251ro-sens");
	listeMotsClefs << "citation";
	listeMotsClefs << QString::fromUtf8("r\303\251f\303\251rence-titre");
	listeMotsClefs << QString::fromUtf8("r\303\251f\303\251rence");
	listeMotsClefs << "nature";
	listeMotsClefs << "rubrique";
	listeMotsClefs << QString::fromUtf8("suppl\303\251ment");
	listeMotsClefs << QString::fromUtf8("entr\303\251e");
	listeMotsClefs << "lien";
	listeMotsClefs << QString::fromUtf8("r\303\251sum\303\251");
	SurlignerMotsClefs(text, listeMotsClefs, formatTexte);

	formatTexte.setFontWeight(QFont::Normal);
	formatTexte.setFontItalic(true);
	listeMotsClefs.clear();
	listeMotsClefs << QString::fromUtf8("marge-sup\303\251rieure");
	listeMotsClefs << QString::fromUtf8("marge-inf303\251rieure");
	listeMotsClefs << "marge-droite";
	listeMotsClefs << "marge-gauche";
	listeMotsClefs << "marge";
	listeMotsClefs << "couleur-fond";
	listeMotsClefs << "couleur-texte";
	listeMotsClefs << QString::fromUtf8("\303\251paisseur-police");
	listeMotsClefs << "style-police";
	listeMotsClefs << "taille-police";
	listeMotsClefs << "nom-police";
	listeMotsClefs << "image-fond";
	listeMotsClefs << "effets-texte";
	SurlignerMotsClefs(text, listeMotsClefs, formatTexte);
}
