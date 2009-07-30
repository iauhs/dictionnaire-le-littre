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

#ifndef CLASSERECHERCHE_H
#define CLASSERECHERCHE_H

#include <QDialog>
#include <QTextDocumentFragment>
#include <QCloseEvent>

#include "ui_classerecherche.h"
#include "classeminuterierouge.h"
#include "classeprincipale.h"

class classePrincipale;

class classeRecherche : public QDialog, public Ui::fenetreRecherche
{
	Q_OBJECT
public:
	classeRecherche(QWidget *parent = 0, Qt::WindowFlags f = 0);

	int nombreEntree;
	QString texteRecherche;
	bool boolArretUrgence;
private:
	QAction *actionExporterHTML,
		*actionExporterODF,
		*actionExporterTXT,
		*actionExporterPDF;
	classePrincipale *fenetrePrincipale;

	QTextDocument *CreerDocument();
	QString CreerEntete(const int nombreIndexEntree);
	void ActiverOuDesactiver(bool boolActiver, const int nombreResultats = -1);
	bool EstSusceptible(QString texte, const Qt::CaseSensitivity respecterCasse,
		const bool boolExpressionRationnelle);
	void AjouterAvertissementAuxResultats(const QString &texte);
protected:
	void closeEvent(QCloseEvent *event);
private slots:
	void Consulter();
	void Chercher(QString texteParametre = QString());
	void EvenementResultatChoisi();
	void FermerOuAnnuler();
	void ApercuImpression(QPrinter *printer);
	void AfficherApercuImpression();
	void Exporter();
	void Imprimer();
	void EvenementAccessibleZoneListe(const QModelIndex &index);
	void EvenementAccessibleAction();
};

#endif
