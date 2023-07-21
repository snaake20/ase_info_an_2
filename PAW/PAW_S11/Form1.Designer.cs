namespace PAW_S11
{
	partial class Form1
	{
		/// <summary>
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.IContainer components = null;

		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		/// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
		protected override void Dispose(bool disposing)
		{
			if (disposing && (components != null))
			{
				components.Dispose();
			}
			base.Dispose(disposing);
		}

		#region Windows Form Designer generated code

		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		private void InitializeComponent()
		{
			this.components = new System.ComponentModel.Container();
			this.menuStrip1 = new System.Windows.Forms.MenuStrip();
			this.incarcaDateToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.previzualizareToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.iesireToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.panel = new System.Windows.Forms.Panel();
			this.CMSPanel = new System.Windows.Forms.ContextMenuStrip(this.components);
			this.schimbaCuloareToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.menuStrip1.SuspendLayout();
			this.CMSPanel.SuspendLayout();
			this.SuspendLayout();
			// 
			// menuStrip1
			// 
			this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.incarcaDateToolStripMenuItem,
            this.previzualizareToolStripMenuItem,
            this.iesireToolStripMenuItem});
			this.menuStrip1.Location = new System.Drawing.Point(0, 0);
			this.menuStrip1.Name = "menuStrip1";
			this.menuStrip1.Size = new System.Drawing.Size(800, 24);
			this.menuStrip1.TabIndex = 0;
			this.menuStrip1.Text = "menuStrip1";
			// 
			// incarcaDateToolStripMenuItem
			// 
			this.incarcaDateToolStripMenuItem.Name = "incarcaDateToolStripMenuItem";
			this.incarcaDateToolStripMenuItem.Size = new System.Drawing.Size(84, 20);
			this.incarcaDateToolStripMenuItem.Text = "Incarca Date";
			this.incarcaDateToolStripMenuItem.Click += new System.EventHandler(this.incarcaDateToolStripMenuItem_Click);
			// 
			// previzualizareToolStripMenuItem
			// 
			this.previzualizareToolStripMenuItem.Name = "previzualizareToolStripMenuItem";
			this.previzualizareToolStripMenuItem.Size = new System.Drawing.Size(90, 20);
			this.previzualizareToolStripMenuItem.Text = "Previzualizare";
			this.previzualizareToolStripMenuItem.Click += new System.EventHandler(this.previzualizareToolStripMenuItem_Click);
			// 
			// iesireToolStripMenuItem
			// 
			this.iesireToolStripMenuItem.Name = "iesireToolStripMenuItem";
			this.iesireToolStripMenuItem.Size = new System.Drawing.Size(46, 20);
			this.iesireToolStripMenuItem.Text = "Iesire";
			// 
			// panel
			// 
			this.panel.ContextMenuStrip = this.CMSPanel;
			this.panel.Dock = System.Windows.Forms.DockStyle.Fill;
			this.panel.Location = new System.Drawing.Point(0, 24);
			this.panel.Name = "panel";
			this.panel.Size = new System.Drawing.Size(800, 426);
			this.panel.TabIndex = 1;
			this.panel.Paint += new System.Windows.Forms.PaintEventHandler(this.panel_Paint);
			// 
			// CMSPanel
			// 
			this.CMSPanel.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.schimbaCuloareToolStripMenuItem});
			this.CMSPanel.Name = "CMSPanel";
			this.CMSPanel.Size = new System.Drawing.Size(163, 26);
			// 
			// schimbaCuloareToolStripMenuItem
			// 
			this.schimbaCuloareToolStripMenuItem.Name = "schimbaCuloareToolStripMenuItem";
			this.schimbaCuloareToolStripMenuItem.Size = new System.Drawing.Size(180, 22);
			this.schimbaCuloareToolStripMenuItem.Text = "Schimba culoare";
			this.schimbaCuloareToolStripMenuItem.Click += new System.EventHandler(this.schimbaCuloareToolStripMenuItem_Click);
			// 
			// Form1
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(800, 450);
			this.Controls.Add(this.panel);
			this.Controls.Add(this.menuStrip1);
			this.MainMenuStrip = this.menuStrip1;
			this.Name = "Form1";
			this.Text = "Form1";
			this.menuStrip1.ResumeLayout(false);
			this.menuStrip1.PerformLayout();
			this.CMSPanel.ResumeLayout(false);
			this.ResumeLayout(false);
			this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.MenuStrip menuStrip1;
		private System.Windows.Forms.ToolStripMenuItem incarcaDateToolStripMenuItem;
		private System.Windows.Forms.ToolStripMenuItem previzualizareToolStripMenuItem;
		private System.Windows.Forms.ToolStripMenuItem iesireToolStripMenuItem;
		private System.Windows.Forms.Panel panel;
		private System.Windows.Forms.ContextMenuStrip CMSPanel;
		private System.Windows.Forms.ToolStripMenuItem schimbaCuloareToolStripMenuItem;
	}
}

