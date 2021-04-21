package org.orca.kprofiler;

import javax.swing.JInternalFrame;
import javax.swing.JDesktopPane;
import javax.swing.JMenu;
import javax.swing.JMenuItem;
import javax.swing.JMenuBar;
import javax.swing.JFrame;
import javax.swing.KeyStroke;
import javax.swing.JFileChooser;
import javax.swing.filechooser.FileNameExtensionFilter;
import java.io.File;
import java.awt.event.*;
import java.awt.*;
import javax.swing.*;
import java.awt.GridLayout;
import java.io.IOException;
import java.lang.ProcessBuilder;
import java.lang.Object;

public class Kprofiler extends JFrame implements ActionListener {
	JDesktopPane desktop;
	File file;
	File orcaDatafile;
	public Kprofiler() {
		super("Orca RT-Bench");

		Dimension screenSize = Toolkit.getDefaultToolkit().getScreenSize();
		setBounds(50, 50, 850, 350);


		//Set up the GUI.
		desktop = new JDesktopPane(); //a specialized layered pane
		//createFrame(); //create first "window"
		setContentPane(desktop);
		setJMenuBar(createMenuBar());

		//Make dragging a little faster but perhaps uglier.
		desktop.setDragMode(JDesktopPane.OUTLINE_DRAG_MODE);
	}

	protected JMenuBar createMenuBar() {
		JMenuBar menuBar = new JMenuBar();
		JMenuItem menuItem;

		JMenu menu1 = new JMenu("File");
		menu1.setMnemonic(KeyEvent.VK_F);
		menuBar.add(menu1);

		menuItem = new JMenuItem("Open schedule file");
		menuItem.setMnemonic(KeyEvent.VK_O);
		menuItem.setAccelerator(KeyStroke.getKeyStroke(
				KeyEvent.VK_O, ActionEvent.ALT_MASK));
		menuItem.setActionCommand("file_opentrace");
		menuItem.addActionListener(this);
		menu1.add(menuItem);

		menuItem = new JMenuItem("Close schedule file");
		menuItem.setMnemonic(KeyEvent.VK_C);
		menuItem.setAccelerator(KeyStroke.getKeyStroke(
				KeyEvent.VK_C, ActionEvent.ALT_MASK));
		menuItem.setActionCommand("file_closetrace");
		menuItem.addActionListener(this);
		menu1.add(menuItem);

		menuItem = new JMenuItem("Quit");
		menuItem.setMnemonic(KeyEvent.VK_Q);
		menuItem.setAccelerator(KeyStroke.getKeyStroke(
				KeyEvent.VK_Q, ActionEvent.ALT_MASK));
		menuItem.setActionCommand("file_quit");
		menuItem.addActionListener(this);
		menu1.add(menuItem);

		JMenu menu2 = new JMenu("Schedule");
		menu1.setMnemonic(KeyEvent.VK_T);
		menuBar.add(menu2);

		menuItem = new JMenuItem("Plot");
		menuItem.setMnemonic(KeyEvent.VK_P);
		menuItem.setAccelerator(KeyStroke.getKeyStroke(
				KeyEvent.VK_P, ActionEvent.ALT_MASK));
		menuItem.setActionCommand("trace_plot");
		menuItem.addActionListener(this);
		menu2.add(menuItem);
		
		
		JMenu menu3 = new JMenu("Orca Scheduler");
		menu1.setMnemonic(KeyEvent.VK_S);
		menuBar.add(menu3);
		
		menuItem = new JMenuItem("Scheduling configuration");
		menuItem.setMnemonic(KeyEvent.VK_B);
		menuItem.setAccelerator(KeyStroke.getKeyStroke(
				KeyEvent.VK_B, ActionEvent.ALT_MASK));
		menuItem.setActionCommand("orca_active");
		menuItem.addActionListener(this);
		menu3.add(menuItem);
		
		
		JMenu menu4 = new JMenu("Help");
		menu1.setMnemonic(KeyEvent.VK_H);
		menuBar.add(menu4);
		menuItem = new JMenuItem("About the orca-rt-bench");
		menuItem.setMnemonic(KeyEvent.VK_R);
		menuItem.setAccelerator(KeyStroke.getKeyStroke(
				KeyEvent.VK_R, ActionEvent.ALT_MASK));
		menuItem.setActionCommand("about_orca_active");
		menuItem.addActionListener(this);
		menu4.add(menuItem);
		
		
		//Item de menu - Help = nele estará o tutorial de uso do orca e falar sobre o Prof. Sergio e o kprofiller

		return menuBar;
	}

	//React to menu selections.
	public void actionPerformed(ActionEvent e) {
		if ("file_opentrace".equals(e.getActionCommand())) {
		JFileChooser fc = new JFileChooser();
		int returnVal = fc.showOpenDialog(Kprofiler.this);
		if (returnVal == JFileChooser.APPROVE_OPTION) {
			file = fc.getSelectedFile();
		}
	}
	if ("file_closetrace".equals(e.getActionCommand())) {
		file = null;
	}

	if ("trace_plot".equals(e.getActionCommand())) {
		if (file == null){
			JOptionPane.showMessageDialog(desktop, "You should open a schedule file first!");
		}else{
			String[] items = {"0.1ms", "0.5ms", "1ms", "2ms", "10ms"}; // Opcoes selecionaveis 
			JComboBox combo = new JComboBox(items);
			combo.setSelectedItem("1ms");	// Opcao inicial das selecionaveis
			JTextField field1 = new JTextField("0.000"); // Caixa de texto que permite input
			JPanel panel = new JPanel(new GridLayout(0, 1));		// Painel das opcoes selecionaveis
			panel.add(new JLabel("Resolution:"));	// nome do painel das opcoes selecionaveis
			panel.add(combo);	// adiciona as opcoes selecionaveis ao painel

			panel.add(new JLabel("Start time (ms):")); // nome do painel de input de ms
			panel.add(field1);						// adiciona o campo de input ao painel
			int result = JOptionPane.showConfirmDialog(null, panel, "Trace plot",
			JOptionPane.OK_CANCEL_OPTION, JOptionPane.PLAIN_MESSAGE); //JOptionPane.OK_CANCEL_OPTION == painel com duas opcoes, ok e cancel - USAR
			if (result == JOptionPane.OK_OPTION) {
				createFrame(file.getAbsolutePath(), Float.parseFloat(field1.getText()), combo.getSelectedItem().toString());
			}
		}
	}
	if("orca_active".equals(e.getActionCommand())){
			ProcessBuilder processBuilder = new ProcessBuilder();
		
				// Opcoes de algoritmos de escalonamento	
				
			String[] schedulingalgorithms = {"EDF", "RM"}; 			// Opcoes selecionaveis 
			JComboBox comboschedulingalgorithms = new JComboBox(schedulingalgorithms);
			comboschedulingalgorithms.setSelectedItem("EDF");		// Opcao inicial das selecionaveis
			JPanel panel = new JPanel(new GridLayout(0, 1));		// Painel das opcoes selecionaveis
			panel.add(new JLabel("Scheduling Algorithm"));			// nome do painel das opcoes selecionaveis
			panel.add(comboschedulingalgorithms);					// adiciona as opcoes selecionaveis ao painel

			
				
				
				
				// Tempo de execucacao desejado (em ms)
			
			JTextField field1ms = new JTextField("0.000");  	// Caixa de texto que permite input
			panel.add(new JLabel("Execution time (ms)"));  		// nome do painel de input de ms
			panel.add(field1ms);								// adiciona o campo de input ao painel
				
				
				
				
				// Arquivo exemplo que deseja aplicar o algoritmo de escalonamento (Navegar e selecionar o arquivo)
				
			panel.add(new JLabel("Data File"));
			JButton b=new JButton("Select the data file to run the scheduling algortihm on");  
			b.setBounds(50,100,95,30);  
			b.addActionListener(new ActionListener(){  
					public void actionPerformed(ActionEvent e){  
						JFileChooser fc = new JFileChooser();
						int returnVal = fc.showOpenDialog(Kprofiler.this);
						if (returnVal == JFileChooser.APPROVE_OPTION) {
								orcaDatafile = fc.getSelectedFile();
								b.setText(orcaDatafile.getPath());
							}  
						}  
					}); 
			panel.add(b);
			
			String pathdir = System.getProperty("user.dir");
			pathdir = pathdir.replaceAll("\\\\", "/");
			
			
			  // Caixa de texto que permite input
			int result = JOptionPane.showConfirmDialog(null, panel, "Orca Scheduler",
			JOptionPane.OK_CANCEL_OPTION, JOptionPane.PLAIN_MESSAGE); //JOptionPane.OK_CANCEL_OPTION == painel com duas opcoes, ok e cancel - USAR
			
			if (result == JOptionPane.OK_OPTION && orcaDatafile != null) {
				//i can keep using / as file separator since it works for both windows and linux
				// i will use fieldpathgeneric and add /examplename since it all be at the same directory 
				processBuilder.command("cmd.exe", "/c", pathdir + "/orca-rt-scheduler.exe", field1ms.getText(), orcaDatafile.getPath(), comboschedulingalgorithms.getSelectedItem().toString()).directory(new File(pathdir));
				
				try{
					Process process = processBuilder.start();
						}catch(IOException deuruim){
													quit();
					}
					
			}else if(result == JOptionPane.OK_OPTION && orcaDatafile == null){
				JOptionPane.showMessageDialog(panel,"You should select a schedule data file first!");
				}
				
		file = new File(pathdir+"/output.orca");
		
	}
	if("about_orca_active".equals(e.getActionCommand())){
		JOptionPane.showMessageDialog(desktop, "The Orca-RT-bench was develop by Anderson Domingues (ti.andersondomingues@gmail.com)\n\nThe graphical user interface was develop using the application kprofiller, provided by Professor Sergio F. Johann (sergio.johann@acad.pucrs.br)\n\nWith the help of Joao Benno (jbweber05@gmail.com) \n\n\n                                              Copyright (C) 2018-2021 Anderson Domingues <ti.andersondomingues@gmail.com> ");
	}
	
	if("file_quit".equals(e.getActionCommand())) {
			quit();
		}
	}

	//Create a new internal frame.
	protected void createFrame(String name, float start_time, String resolution) {
		ProfilerFrame frame;

		System.out.printf(name);
		frame = new ProfilerFrame(name, start_time, resolution);
		frame.setVisible(true); //necessary as of 1.3
		desktop.add(frame);
//		try{
//			frame.setMaximum(true);
//		} catch (java.beans.PropertyVetoException e){}
		try {
			frame.setSelected(true);
		} catch (java.beans.PropertyVetoException e) {}
	}

	//Quit the application.
	protected void quit() {
		System.exit(0);
	}

	/**
	 * Create the GUI and show it.  For thread safety,
	 * this method should be invoked from the
	 * event-dispatching thread.
	 */
	private static void createAndShowGUI() {
		//Make sure we have nice window decorations.
		JFrame.setDefaultLookAndFeelDecorated(true);

		//Create and set up the window.
		Kprofiler frame = new Kprofiler();
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

		//Display the window.
		frame.setVisible(true);
	frame.setExtendedState(frame.getExtendedState() | JFrame.MAXIMIZED_BOTH);

	}

	public static void main(String[] args) {
		//Schedule a job for the event-dispatching thread:
		//creating and showing this application's GUI.
		javax.swing.SwingUtilities.invokeLater(new Runnable() {
			public void run() {
				createAndShowGUI();
			}
		});
	}
}
