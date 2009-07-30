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

#include "classeconjugaison.h"
#include "classeprincipale.h"

classeConjugaison::classeConjugaison(bool boolModeAccessible, QWidget *parent,
		Qt::WindowFlags f) : QDialog(parent, f)
{
	setupUi(this);
	setFixedSize(size());

	QMenu *menuExporter(new QMenu(this));
	classePrincipale *fenetrePrincipale(qobject_cast<classePrincipale *>(parent));
	actionExporterHTML = new QAction(fenetrePrincipale->actionExporterHTML->text(), this);
	actionExporterODF = new QAction(fenetrePrincipale->actionExporterODF->text(), this);
	actionExporterTXT = new QAction(fenetrePrincipale->actionExporterTXT->text(), this);
	actionExporterPDF = new QAction(fenetrePrincipale->actionExporterPDF->text(), this);
	menuExporter->addAction(actionExporterHTML);
	menuExporter->addAction(actionExporterODF);
	menuExporter->addAction(actionExporterPDF);
	menuExporter->addAction(actionExporterTXT);
	connect(actionExporterHTML, SIGNAL(triggered()), this, SLOT(Exporter()));
	connect(actionExporterODF, SIGNAL(triggered()), this, SLOT(Exporter()));
	connect(actionExporterPDF, SIGNAL(triggered()), this, SLOT(Exporter()));
	connect(actionExporterTXT, SIGNAL(triggered()), this, SLOT(Exporter()));
	boutonExporter->setMenu(menuExporter);
	connect(boutonImprimer, SIGNAL(clicked()), this, SLOT(Imprimer()));
	connect(boutonAfficherApercuImpression, SIGNAL(clicked()), this,
			SLOT(AfficherApercuImpression()));

	if(boolModeAccessible) {
		foreach(QLabel *etiquette, findChildren<QLabel *>())
			etiquette->setAccessibleName(QString::fromUtf8("\303\211tiquette ")
					+ etiquette->text().replace("&", ""));

		foreach(QPushButton *bouton, findChildren<QPushButton *>())
			bouton->setAccessibleName("Bouton " + bouton->text().replace("&", ""));

		foreach(QToolButton *bouton, findChildren<QToolButton *>()) {
			bouton->setAccessibleName("Bouton " + bouton->toolTip()
					+ (bouton->menu() ? QString::fromUtf8(
					" (ce bouton ouvre un sous-menu)") : ""));
			bouton->setToolTip("");
		}

		foreach(QAction *action, findChildren<QAction *>())
			if(action->isSeparator() == false)
				connect(action, SIGNAL(hovered()), this,
						SLOT(EvenementAccessibleAction()));
	}
}

QString classeConjugaison::CreerEntete(QLabel *etiquette)
{
	QString texteOnglet(onglet->tabText(onglet->indexOf(etiquette->parentWidget())));
	if(texteOnglet[texteOnglet.length() - 1] > 0x2080)
		texteOnglet.resize(texteOnglet.length() - 2);
	texteOnglet.replace("&", "");
	QString texteEtiquette(etiquette->text());
	texteEtiquette[0] = texteEtiquette[0].toLower();
	texteEtiquette.replace("&", "");

	const QString texte("<br><div style=\"font-family:'DejaVu Serif'; font-size:12pt; "
			"font-weight: bold;\">" + texteOnglet + " " + texteEtiquette
			+ "</div>");
	return texte;
}

QTextDocument *classeConjugaison::CreerDocument()
{
	QTextDocument *document = new QTextDocument(this);
	QTextCursor curseur(document);
	const QString texte("<div style=\"font-family:'DejaVu Serif'; font-size:14pt; "
			"font-weight: bold;\" align=\"center\">Conjugaison du verbe <i>"
			+ windowTitle() + "</i></div><br>");
	curseur.insertHtml(texte);
	curseur.insertHtml(CreerEntete(etiquetteIndicatifPresent));
	curseur.insertHtml(navigateurIndicatifPresent->toHtml());
	curseur.insertHtml(CreerEntete(etiquetteIndicatifImparfait));
	curseur.insertHtml(navigateurIndicatifImparfait->toHtml());
	curseur.insertHtml(CreerEntete(etiquetteIndicatifPasseSimple));
	curseur.insertHtml(navigateurIndicatifPasseSimple->toHtml());
	curseur.insertHtml(CreerEntete(etiquetteIndicatifFuturSimple));
	curseur.insertHtml(navigateurIndicatifFuturSimple->toHtml());
	curseur.insertHtml(CreerEntete(etiquetteSubjonctifPresent));
	curseur.insertHtml(navigateurSubjonctifPresent->toHtml());
	curseur.insertHtml(CreerEntete(etiquetteSubjonctifImparfait));
	curseur.insertHtml(navigateurSubjonctifImparfait->toHtml());
	curseur.insertHtml(CreerEntete(etiquetteConditionnelPresent));
	curseur.insertHtml(navigateurConditionnelPresent->toHtml());
	curseur.insertHtml(CreerEntete(etiquetteImperatifPresent));
	curseur.insertHtml(navigateurImperatifPresent->toHtml());
	curseur.insertHtml(CreerEntete(etiquetteParticipePresent));
	curseur.insertHtml(navigateurParticipePresent->toHtml());
	curseur.insertHtml(CreerEntete(etiquetteParticipePasse));
	curseur.insertHtml(navigateurParticipePasse->toHtml());
	return document;
}

void classeConjugaison::Exporter()
{
	QTextDocument *document = CreerDocument();

	QString texteFiltre;
	QStringList listeExtensions;
	if(sender() == actionExporterODF) {
		texteFiltre = "Fichiers OpenDocument (*.odf)";
		listeExtensions << "odf";
	} else if(sender() == actionExporterTXT) {
		texteFiltre = "Fichiers texte simple (*.txt)";
		listeExtensions << "txt";
	} else if(sender() == actionExporterPDF) {
		texteFiltre = "Fichiers PDF (*.pdf)";
		listeExtensions << "pdf";
	} else {
		texteFiltre = "Fichiers HTML (*.html *.htm)";
		listeExtensions << "html" << "htm";
	}

	QString texteNomFichier = QFileDialog::getSaveFileName(this,
			boutonExporter->text().replace("&", ""),
			QString(), texteFiltre + ";;Tous les fichiers (*)");

	if (texteNomFichier.isEmpty() == false) {
		if(listeExtensions.contains(
				QFileInfo(texteNomFichier).suffix().toLower()) == false)
			texteNomFichier += "." + listeExtensions.at(0);

		if(listeExtensions.at(0) == "pdf") {
			QPrinter imprimate(QPrinter::HighResolution);
			imprimate.setDocName(windowTitle());
			imprimate.setOutputFormat(QPrinter::PdfFormat);
			imprimate.setOutputFileName(texteNomFichier);
			document->print(&imprimate);
		}
		else {
			QTextDocumentWriter exporteur(texteNomFichier);
			exporteur.setFormat(listeExtensions.at(0).toAscii());
			if (exporteur.write(document) == false) {
				classePrincipale *fenetrePrincipale(
						qobject_cast<classePrincipale *>(parent()));
				QMessageBox::warning(this, fenetrePrincipale->windowTitle(),
						QString::fromUtf8("Impossible d'\303\251"
						"crire le fichier ") + texteNomFichier + ".");
			}
		}
	}

	delete document;
}

void classeConjugaison::Imprimer()
{
	QTextDocument *document = CreerDocument();
	QPrinter imprimante(QPrinter::HighResolution);
	imprimante.setDocName(windowTitle());
	QPrintDialog *fenetreImprimer = new QPrintDialog(&imprimante, this);
	fenetreImprimer->setWindowTitle(boutonImprimer->text().replace("&", ""));
	if (fenetreImprimer->exec() == QDialog::Accepted)
		document->print(&imprimante);
	delete fenetreImprimer;
	delete document;
}

void classeConjugaison::AfficherApercuImpression()
{
	QPrinter imprimante(QPrinter::HighResolution);
	imprimante.setDocName(windowTitle());
	QPrintPreviewDialog fenetreApercu(&imprimante, this);
	connect(&fenetreApercu, SIGNAL(paintRequested(QPrinter *)), this,
			SLOT(ApercuImpression(QPrinter *)));
	fenetreApercu.exec();
}

void classeConjugaison::ApercuImpression(QPrinter *printer)
{
	QTextDocument *document = CreerDocument();
	document->print(printer);
	delete document;
}

void classeConjugaison::EvenementAccessibleAction()
{
	QAction *action(qobject_cast<QAction *>(sender()));
	QString texte(action->iconText());
	if(action->isCheckable())
		texte += QString(" (cette action ") + (action->isChecked() ? "est"
				: "n'est pas") + QString::fromUtf8(" coch\303\251e)");
	foreach(QMenu *menu, findChildren<QMenu *>())
		if(menu->actions().contains(action)) {
			if(menu->accessibleName() != texte)
				menu->setAccessibleName(texte);;
			break;
		}
}
