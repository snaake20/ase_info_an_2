using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;
using System.Xml;

namespace PAW_S07
{
    public partial class Seminar7 : Form
    {
        public Seminar7()
        {
            InitializeComponent();
        }

        private void btnParsare_Click(object sender, EventArgs e)
        {
            StreamReader sr = new StreamReader("bnr.xml");
            string str = sr.ReadToEnd();
            sr.Close();
            XmlReader reader = XmlReader.Create(new StringReader(str));
            while (reader.Read())
            {
                if (reader.Name == "PublishingDate" && reader.NodeType == XmlNodeType.Element)
                {
                    reader.Read();
                    tbData.Text = reader.Value;
                }
                if (reader.Name == "Rate" && reader.NodeType == XmlNodeType.Element)
                {
                    string attribute = reader["currency"];
                    if (attribute == "EUR")
                    {
                        reader.Read();
                        tbEur.Text = reader.Value;
                    }
                    if (attribute == "USD")
                    {
                        reader.Read();
                        tbUsd.Text = reader.Value;
                    }
                    if (attribute == "GBP")
                    {
                        reader.Read();
                        tbGbp.Text = reader.Value;
                    }
                    if (attribute == "XAU")
                    {
                        reader.Read();
                        tbXau.Text = reader.Value;
                    }
                }
            }
        }

        private void btnGenerare_Click(object sender, EventArgs e)
        {
            MemoryStream memStream = new MemoryStream();
            XmlTextWriter writer = new XmlTextWriter(memStream, Encoding.UTF8);

            writer.Formatting = Formatting.Indented;

            writer.WriteStartDocument();

            writer.WriteStartElement("CursValutar");
            
            {
                writer.WriteStartElement("DataCurs");
                writer.WriteValue(tbData.Text);
                writer.WriteEndElement();

                writer.WriteStartElement("CursEUR");
                writer.WriteAttributeString("atribut", "EUR");
                writer.WriteValue(tbEur.Text);
                writer.WriteEndElement();

                writer.WriteStartElement("CursUSD");
                writer.WriteAttributeString("atribut", "USD");
                writer.WriteValue(tbUsd.Text);
                writer.WriteEndElement();

                writer.WriteStartElement("CursGBP");
                writer.WriteAttributeString("atribut", "GBP");
                writer.WriteValue(tbGbp.Text);
                writer.WriteEndElement();

                writer.WriteStartElement("CursXAU");
                writer.WriteAttributeString("atribut", "XAU");
                writer.WriteValue(tbXau.Text);
                writer.WriteEndElement();
            }
            
            writer.WriteEndElement();
            
            writer.WriteEndDocument();

            writer.Close();

            string str = Encoding.UTF8.GetString(memStream.ToArray());

            StreamWriter sw = new StreamWriter("fisier.xml");
            sw.WriteLine(str);
            sw.Close();
            MessageBox.Show("Date Exportate!");
        }

        private void btnTv_Click(object sender, EventArgs e)
        {
            TreeNode parinte = new TreeNode("CursValutar");
            tvXml.Nodes.Add(parinte);
            TreeNode copilData = new TreeNode(tbData.Text);
            parinte.Nodes.Add(copilData);
            TreeNode copilEur = new TreeNode(tbEur.Text);
            copilData.Nodes.Add(copilEur);
            TreeNode copilUsd = new TreeNode(tbUsd.Text);
            copilData.Nodes.Add(copilUsd);
            TreeNode copilGbp = new TreeNode(tbGbp.Text);
            copilData.Nodes.Add(copilGbp);
            TreeNode copilXau = new TreeNode(tbXau.Text);
            copilData.Nodes.Add(copilXau);

            tvXml.ExpandAll();

        }

        private void exportToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (tvXml.Nodes != null)
            {
                MemoryStream memStream = new MemoryStream();
                XmlTextWriter writer = new XmlTextWriter(memStream, Encoding.UTF8);

                writer.Formatting = Formatting.Indented;

                writer.WriteStartDocument();

                foreach (TreeNode parinte in tvXml.Nodes)
                {
                    writer.WriteStartElement("CursValutar");
                    foreach (TreeNode copil in parinte.Nodes)
                    {
                        writer.WriteStartElement("Data");
                        writer.WriteAttributeString("data", copil.Text);
                        foreach (TreeNode nepot in copil.Nodes)
                        {
                            writer.WriteStartElement("Valuta");
                            writer.WriteValue(nepot.Text);
                            writer.WriteEndElement();
                        }
                        writer.WriteEndElement();
                    }
                    writer.WriteEndElement();
                }

                writer.WriteEndDocument();

                writer.Close();

                string str = Encoding.UTF8.GetString(memStream.ToArray());

                StreamWriter sw = new StreamWriter("tv.xml");
                sw.WriteLine(str);
                sw.Close();
                MessageBox.Show("Date Exportate!");
            }
        }
    }
}
