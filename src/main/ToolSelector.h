#ifndef TOOLSELECTOR_H
#define TOOLSELECTOR_H

#include <QWidget>
#include <QPushButton>
#include <QButtonGroup>
#include <QGridLayout>
#include <QStackedWidget>

#include "Component.h"
#include "Tool.h"

/** @brief This class manages the tool-selection process of Happah
 * 
 * For this purpose, this class provides the selection widget itself 
 * and a widget for more elaborated tool settings.
 */
class ToolSelector: public QWidget {
Q_OBJECT

public:
	ToolSelector(QWidget* parent);

	~ToolSelector();

	/** @brief Adds new tool to tool selector.
	 *
	 * This function adds a new entry to the tool selector and its widgets.
	 * @param toolButton Button that will be shown in the selector widget.
	 *    This button will be resized to fit into the grid.
	 * @param toolSettings Widget which will be shown when this tool was
	 *    selected by the user.
	 */
	void addTool(Tool* tool);

	/** @brief Returns settings dialog widget.
	 *
	 * @return Widget which shows tool-settings-widget of the currently
	 *    selected tool. To be placed somewhere in the application.
	 */
	QWidget* getSettingsWidget();

private:
	int toolCount_; /**< Number of registered tools. */
	int currToolID_; /**< Identifies currently selected tool. */
	static const int BUTTONS_PER_ROW = 4; /**< Number of tools per row in selector widget. */

	QGridLayout* selectorGrid_; /**< Local layout for selection buttons. */
	QButtonGroup* buttonGroup_; /**< Handles click events of tool selection. */
	QStackedWidget* settingsWidgetStack_; /**< Widget to display tool settings. */
	QList<Tool*> toolList_; /**< List of registered tools. */

private slots:
	void toolSelected(int toolID);
	void newComponent(Component* component);

signals:
	void emitComponent(Component* component);
};

#endif
