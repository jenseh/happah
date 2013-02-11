#ifndef COMPONENTLIST_H
#define COMPONENTLIST_H

#include <QListWidget>
#include <string>


class ComponentList: public QListWidget {
Q_OBJECT

private:
	unsigned int m_uniqueIDCounter;

public:
	ComponentList( QWidget* parent = 0 );
	~ComponentList();


public slots:
    unsigned int addComponent( std::string displayedName );
    unsigned int addNewItem( std::string displayedName );
	void deleteItem( unsigned int itemID );
	void selectItem( unsigned int itemID );
	void deleteButtonPressed();

private slots:
	void changeItem( QListWidgetItem* current, QListWidgetItem* previous );

signals:
	void itemDeleted( unsigned int itemID );
	void itemEdit( unsigned int itemID );
	void itemChanged( unsigned int itemID );
	void selectionChanged( unsigned int itemID );
	void deleteCurrent( std::string name );

};

#endif // COMPONENTLIST_H
