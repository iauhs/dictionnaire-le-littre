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

#ifndef CLASSEPRINCIPALE_H
#define CLASSEPRINCIPALE_H

#include <QCoreApplication>
#include <QMainWindow>
#include <QMessageBox>
#include <QFile>
#include <QStringList>
#include <QRegExp>
#include <QXmlStreamReader>
#include <QTextStream>
#include <QFileDialog>
#include <QTextCodec>
#include <QPrintDialog>
#include <QPrinter>
#include <QDir>
#include <QUrl>
#include <QSystemTrayIcon>
#include <QClipboard>
#include <QScrollBar>
#include <QTextDocumentWriter>
#include <QHash>
#include <QPrintPreviewDialog>
#include <QResource>
#include <QDesktopWidget>
#include <QAccessible>

#include "ui_classeprincipale.h"
#include "classerecherche.h"
#include "classesurligneur.h"
#include "classetypographie.h"

enum {
	PLURIEL =		1,
	MASCULIN =		2,
	FEMININ =		4,
	PREMIEREPERSONNE =	8,
	TROISIEMEPERSONNE =	16,
	INDICATIF =		32,
	PARTICIPE =		64,
	PASSE =			128,
	IMPARFAIT =		256,
	CONDITIONNEL =		512,
	SUBJONCTIF =		1024,
	FUTUR =			2048,
	IMPERATIF =		4096,
	INFINITIF =		8192
};

struct structureFormeFlechie {
	QString texteForme;
	int nombreIndexEntree;
};

struct structureEntree {
	QString texteEntree;
	int nombrePositionFichier;
};

class classeSurligneur;

class classeRecherche;

class classePrincipale : public QMainWindow, public Ui::fenetrePrincipale
{
	Q_OBJECT;
public:
	QHash<int, structureEntree> tableEntrees;
	int nombrePartieEnMemoire;
	QString texteRepertoire;
	bool boolModeAccessible;

	classePrincipale(const QString &texteDossier, const QString &texteTitre,
			bool boolRemiseANeuf, QWidget *parent = 0,
			Qt::WindowFlags flags = 0);
	~classePrincipale();
	QString RecupererArticle(int nombreIndexEntree);
	int CompterFormesFlechies() { return 427704; }
	int CompterEntrees() { return 78427; }
	QString LireFormeFlechie(int nombreIndexFormeFlechie);
	QString LireEntree(int nombreIndexEntree);
	void Selectionner(QListView *boite, const int nombreIndex);
	int TrouverIndexChoisi(QListView *boite);
	QTextCursor ChercherDocument(const QString &texteRecherche, QTextDocument *document,
			QTextDocument::FindFlags optionsRecherche,
			bool boolExpressionRationnelle);
	QString XMLVersHTML(const QString &texteXML, bool boolAfficher = false);
	QString ExtraireLemme(const QString &texte);
private:
	QHash<int, structureFormeFlechie> tableFormesFlechies;

	classeRecherche *fenetreRecherche;
	classeSurligneur *surligneur;
	QAction *actionReduire,
		*actionMaximiser,
		*actionRestaurer,
		*actionPressePapiers;
	QSystemTrayIcon *icone;

	QString texteFeuilleStyle;

	void SauterBalise(QXmlStreamReader *lecteur, const QString &texteBalise);
	QString LireBalise(QXmlStreamReader *lecteur, const QString &texteBalise);
	void Naviguer(QString texteMot, bool boolIcone = false);
	void ClearHighlight();
	void ActiverOuDesactiverHistorique(const int nombreIndexSelection);
	QString TrouverTextePressePapiers();
	bool EstHAspire(const int nombreIndexEntree);
	QChar LettreSansAccent(const QChar lettre);
	bool SontEgaux(const QString &texteConsultation, const QString &texte,
			bool boolNegligerAccents);
	QString EnleverAccents(const QString &texte);
	bool EstVoyelle(QChar lettre);
	QString ConvertirTableauEnHTML(const QMultiMap<int, QString> &tableau,
			bool boolHAspire, int nombreStylePersonnel = 0);
	void RestaurerEtatDictionnaire(bool boolRemiseANeuf);
	void EnregistrerEtatDictionnaire();
	QString XMLVersTexteAccessible(const QString &texteXML);
protected:
	bool eventFilter(QObject *obj, QEvent *event);
	void changeEvent(QEvent *event);
private slots:
	void ApercuImpression(QPrinter *printer);
	void AfficherApercuImpression();
	void ChercherArticle(QString texteParametre = QString());
	void Consulter(bool boolDefilerSeulement = false);
	void EvenementChoixEntree(const QItemSelection &selected,
			const bool boolAjouterAHistorique = true);
	void EvenementHistoriqueSelection();
	void EvenementChoixSens();
	void EvenementChoixForme(const QItemSelection &selected);
	void ReculerOuAvancerHistorique();
	void Exporter();
	void ExporterBalises();
	void Imprimer();
	void EvenementModesLecture();
	void AProposDuLogiciel();
	void AfficherPortrait();
	void ChercherTousLesArticles();
	void EvenementClicLien(const QUrl &src);
	void ReculerOuAvancerEntrees();
	void AfficherPleinEcran(bool checked);
	void EvenementIcone(QSystemTrayIcon::ActivationReason reason);
	void NaviguerPressePapiers();
	void LirePreface();
	void AfficherFlexion();
	void EvenementCopieDisponible(bool yes);
	void Copier();
	void EvenementDoubleClique();
	void EvenementSaisie();
	void Restaurer();
	void ChangerTypographie();
	void EvenementAccessibleAction();
	void EvenementAccessibleZoneListe(const QModelIndex &index);
signals:
	void SignalReduireEnIcone();
	void SignalDoubleClique();
};

#endif
